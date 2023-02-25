/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME   "rodriguesexe"
#define IO_KEY        "aio_fvYB696PaGWe2htTjJhLKryS2rzx"

/******************************* WIFI **************************************/

#define WIFI_SSID   "AQTESTE"
#define WIFI_PASS   "adgjmptw"

#include "AdafruitIO_WiFi.h"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/****************************************************************************/
