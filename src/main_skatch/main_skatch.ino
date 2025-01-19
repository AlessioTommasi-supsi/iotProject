#include <Arduino.h>


#include "SystemState.h"

#include <vector>
#include <string>
#include "WiFiManager.h"
#include "PinoutData.h"
#include "Esp32_38pin.h"
#include "Pin.h"

const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";

SystemState *systemState;

PinoutData *pinoutData;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta
  }
  Serial.println("Inizializzazione porta seriale effettuata!");
  try
  {
    systemState = SystemState::getInstance();

    
    //WiFiManager *wifiManager = new WiFiManager(ssid, password); // per comodita versione finale usa quello sotto
    WiFiManager *wifiManager = new WiFiManager();
    pinoutData = new Esp32_38pin();
    //pinoutData->initializePins();
    


    systemState->setWifiManager(wifiManager);
    systemState->setPinoutData(pinoutData);

  }
  catch (const std::exception &e)
  {
    Serial.println("Errore durante la connessione alla rete Wi-Fi!");
  }

  Serial.println("Inizializzazione completata!");

  while (SystemState::isStopped == false && systemState->getState() != State::ERROR)
  {  
    //Serial.println("Updating state...");
    systemState->update();
    delay(5000); // controllo ogni secondo se devo fermarmi
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
