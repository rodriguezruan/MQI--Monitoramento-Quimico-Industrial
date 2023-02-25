// INCLUSÃO DE BIBLIOTECAS
#include <A2a.h>
#include "config.h"
#include <SoftwareSerial.h>

SoftwareSerial swSer(14, 12);

// DEFINIÇÃO DO ENDEREÇO DO SLAVE
#define endereco 0x08  // ENDEREÇO HEXADECIMAL

//DEFINIÇÕES
#define tempoAtualizacao 15000
#define LIGA LOW
#define DESLIGA HIGH

// DEFINIÇÕES DE PINOS DO SLAVE
#define pinRele 6

// INSTANCIANDO OBJETOS


AdafruitIO_Feed *qualidadedoar = io.feed("qualidadedoar");
AdafruitIO_Feed *co2 = io.feed("co2");
AdafruitIO_Feed *rele = io.feed("rele");

// DECLARAÇÃO DE FUNÇÕES
void configuraMQTT();
void retornoRele(AdafruitIO_Data *data);
bool monitoraqualidadedoar();
bool monitoraco2();

// DECLARAÇÃO DE VARIÁVEIS
unsigned long controleTempo = 0;
bool comandoRecebido = false;

float _qualidadedoar;
float _co2;
//_qualidadedoar = (float)mq135;  //corrigir essa parte do c´digo com a ana letícia, enviar info pro adafruit

void setup() {
  // INICIA A COMUNICAÇÃO SERIAL
  Serial.begin(9600);
  while (!Serial)
    ;

  swSer.begin(9600);


  configuraMQTT();

  Serial.println("Atualizando estado do Rele");
  rele->get();
  io.run();

  Serial.println("Fim setup()");
}

String rx = "";
String mq135, mq7;


void loop() {

  recebe_dados();



  io.run();

  if (millis() > controleTempo + tempoAtualizacao) {

    if (monitoraqualidadedoar()) {
      controleTempo = millis();
      qualidadedoar->save(_qualidadedoar);
    }

    if (monitoraco2()) {
      controleTempo = millis();
      co2->save(_co2);
    }
  }
}

// IMPLEMENTO DE FUNÇÕES
void configuraMQTT() {
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  rele->onMessage(retornoRele);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void retornoRele(AdafruitIO_Data *data) {
  Serial.print("Controle Recebido <- ");
  Serial.println(data->value());

  String estadoRele = data->value();

  if (estadoRele == "ON") {
    Serial.println("Acionando Rele");
  } else if (estadoRele == "OFF") {
    Serial.println("Desligando Rele");
  }
}

bool monitoraqualidadedoar() {
  return true;
}

bool monitoraco2() {
  static int leituraAnt;
  return true;
}

void recebe_dados() {
  if (swSer.available() > 0) {
    Serial.println("lendo dados");
    rx = swSer.readStringUntil('#');
    Serial.println(rx);
    delay(1000);
    int pi = rx.indexOf(",");
    int pf = rx.indexOf("@");
    mq135 = rx.substring(0, pi);
    mq7 = rx.substring(pi + 1, pf);

    _co2 = mq7.toFloat();
    _qualidadedoar = mq135.toFloat();


    Serial.println(rx);
    Serial.println(pi); 
    Serial.println(pf);
    Serial.println(mq135);
    Serial.println(mq7);
  }
}