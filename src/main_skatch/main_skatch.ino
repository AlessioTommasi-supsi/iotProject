#include <Arduino.h>

#include "SystemState.h"

#include <vector>
#include <string>
#include "WiFiManager.h"
#include "PinoutData.h"
#include "Esp32_30pin.h"
#include "Pin.h"
#include "Config.h"

const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";

SystemState *systemState;
PinoutData *pinoutData;

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  
  try
  {
    systemState = SystemState::getInstance();

    //pinoutData = new Esp32_38pin(); //pinout esp scollegato dalla board
    
    pinoutData = new Esp32_30pin();
    systemState->setPinoutData(pinoutData);
    
    //WiFiManager *wifiManager = new WiFiManager(ssid, password); // per comodita versione finale usa quello sotto
    WiFiManager *wifiManager = new WiFiManager();
    
    systemState->setWifiManager(wifiManager);
  }
  catch (...)
  {
    Serial.println("Errore durante il setup delle funzionalita");
  }

  Serial.println("Inizializzazione completata!");

  while (SystemState::isStopped == false && systemState->getState() != State::ERROR)
  {  
    //Serial.println("Updating state...");
    systemState->update();
    
    // Controllo riconnessione WiFi automatica ogni 30 secondi
    WiFiManager *wifiManager = systemState->getWifiManager();
    if (wifiManager != nullptr)
    {
      wifiManager->checkConnection();
    }
    
    delay(SYSTEM_CHECK_INTERVAL); // controllo ogni 5 secondi
  }
  Serial.println("System stopped!");

  destroy();
}

void loop(){
  
}

void destroy()
{
  // delete slaveModbus;
  //delete masterModbus;
  //delete systemState;
}
