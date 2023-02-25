
// INCLUSÃO DE BIBLIOTECAS
#include <A2a.h>
#include "MQ7.h"
#include <MQ135.h>

//mq7
#define A_PIN 2
#define VOLTAGE 5
#define PIN_MQ135 A0

// DEFINIÇÃO DO ENDEREÇO DO SLAVE
#define endereco 8

// INSTANCIANDO OBJETOS
A2a arduinoMaster;

// inicializa o dispositivo mq7
MQ7 mq7(A_PIN, VOLTAGE);
//mq135 int
MQ135 mq135_sensor(PIN_MQ135);
float co2 = 21.0; 
float nh4 = 25.0; 


void setup() {

	Serial.begin(9600);
	while (!Serial) {
		;	// espera a comunicação serial
	}
  Serial1.begin(9600);
//mq7
	Serial.println(""); 	// adiciona uma nova linha

	Serial.println("Calibrating MQ7");
	mq7.calibrate();		// calculates R0
	Serial.println("Calibration done!");
  //---------------------------------------------------

  // INICIA A COMUNICAÇÃO ENTRE ARDUINOS COMO SLAVE NO ENDEREÇO DEFINIDO
  arduinoMaster.begin(endereco);

  // FUNÇÕES PARA COMUNICAÇÃO
}

void loop() {


//---------------------------------------------

//mq135

  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(co2, nh4);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM()*1000;
  float correctedPPM = mq135_sensor.getCorrectedPPM(co2, nh4);

             //mq135                                    //mq7
  Serial1.print(ppm); Serial1.print(",");   Serial1.println(mq7.readPpm()*1000); Serial1.print("@"); Serial1.print("#");
  //LINHA
 // Serial.println(""); //espaço que será excluido

	delay(1000);

//#######################################################################################

}

void receberDados() {
  arduinoMaster.receiveData(); 
}

void enviarDados() {
  arduinoMaster.sendData(); 
}
