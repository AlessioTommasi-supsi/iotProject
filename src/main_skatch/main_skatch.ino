#include <Arduino.h>
//#include "WebServer.h"
#include "MasterModbus.h"
#include "SlaveModbus.h"
#include "SystemState.h"

#include <vector>
#include <string>
#include "WiFiManager.h"


const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";

SystemState *systemState;

SlaveModbus *slaveModbus;

MasterModbus *masterModbus;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta
  }

  pinMode(32, OUTPUT);   // Set GPIO 32 as an output
  digitalWrite(32, LOW); // Set initial state for GPIO 32

  /*
  my_webServer = new WebServer(ssid, password);
  my_webServer->begin();
  */
  try
  {
    systemState = SystemState::getInstance();
    // Initialize the SlaveModbus with the correct pins
    
    masterModbus = new MasterModbus();
    //WiFiManager *wifiManager = new WiFiManager(ssid, password); // per comodita versione finale usa quello sotto
    WiFiManager *wifiManager = new WiFiManager();

    systemState->setWifiManager(wifiManager);

    slaveModbus = new SlaveModbus(23, 32);
  }
  catch (const std::exception &e)
  {
    Serial.println("Errore durante la connessione alla rete Wi-Fi! o master modbus!");
  }

  while (SystemState::isStopped == false && systemState->getState() != State::ERROR)
  {
    delay(1000); // controllo ogni secondo se devo fermarmi
  }

  destroy();
}


void loop(){
  
}

void destroy()
{
  // delete slaveModbus;
  delete masterModbus;
  delete systemState;
}
