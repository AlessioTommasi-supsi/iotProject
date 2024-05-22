#include <Arduino.h>
#include "WebServer.h"
//#include "MasterModbus.h"
#include "SlaveModbus.h"


const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";
WebServer webServer(ssid, password);

SlaveModbus *slaveModbus;
//MasterModbus masterModbus;

void setup()
{
  Serial.begin(1100);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta a
  }

  slaveModbus = new SlaveModbus();

  Serial.println("La porta seriale è pronta! Hello, world!");

  webServer.begin();

  delay(50000);

  destroy();
}

void destroy()
{
  delete slaveModbus;
}

void loop()
{
  delay(50000);
}
