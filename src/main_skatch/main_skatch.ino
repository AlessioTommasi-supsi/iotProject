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
  Serial.begin(9600);
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

  /*
  for (int i = 0; i < 10; i++)
  {
    masterModbus->task();
    systemState->pushRegister(122, masterModbus->readHoldingFloatRegisters(122));
    systemState->pushRegister(500, masterModbus->readHoldingIntRegisters(500));
    delay(50);
  }
  */
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
