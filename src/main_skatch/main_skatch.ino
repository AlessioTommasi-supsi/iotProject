#include <Arduino.h>


#include "SystemState.h"

#include <vector>
#include <string>
#include "WiFiManager.h"
#include "PinoutData.h"
#include "Esp32_38pinBoard.h"
#include "Esp32_30pin.h"
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

    pinoutData = new Esp32_30pin();
    systemState->setPinoutData(pinoutData);
    //pinoutData = new Esp32_38pin();
    //pinoutData = new Esp32_38pinBoard();asd
    

    WiFiManager *wifiManager = new WiFiManager(ssid, password); // per comodita versione finale usa quello sotto
    //WiFiManager *wifiManager = new WiFiManager();
    
    


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
