#include <Arduino.h>
#include "WebServer.h"
#include "MasterModbus.h"
//#include "SlaveModbus.h"
#include "SystemState.h"


const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";
WebServer webServer(ssid, password);

SystemState *systemState;

//SlaveModbus *slaveModbus;

MasterModbus *masterModbus;

void setup()
{
  Serial.begin(1100);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta a
  }

  systemState = SystemState::getInstance();
  //slaveModbus = new SlaveModbus();
  masterModbus = new MasterModbus();

  Serial.println("La porta seriale è pronta! Hello, world!");

  webServer.begin();

  //systemState->setState(State::INIT);

  while (true)
  {
    masterModbus->task();
    systemState->pushRegister(122, masterModbus->readHoldingFloatRegisters(122));
    delay(5000);
  }
  
  
  delay(50000);

  destroy();
}

void destroy()
{
  //delete slaveModbus;
  delete masterModbus;
}

void loop()
{
  delay(500);
}
