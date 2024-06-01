#include <Arduino.h>
//#include "WebServer.h"
#include "MasterModbus.h"
//#include "SlaveModbus.h"
#include "SystemState.h"

#include <vector>
#include <string>
#include "WiFiManager.h"


const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";
//WebServer *my_webServer;

SystemState *systemState;

//SlaveModbus *slaveModbus;

MasterModbus *masterModbus;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta a
  }

  systemState = SystemState::getInstance();
  //slaveModbus = new SlaveModbus();
  masterModbus = new MasterModbus();

  Serial.println("La porta seriale è pronta! Hello, world!");

  /*
  my_webServer = new WebServer(ssid, password);
  my_webServer->begin();
  */

  WiFiManager *wifiManager = new WiFiManager(ssid, password);

  while (SystemState::isStopped == false && systemState->getState() != State::ERROR)
  {
    delay(1000);//controllo ogni secondo se devo fermarmi
  }
  
  

  destroy();
}

void destroy()
{
  //delete slaveModbus;
  delete masterModbus;
  delete systemState;
}

void loop()
{
  //delay(5000);
}
