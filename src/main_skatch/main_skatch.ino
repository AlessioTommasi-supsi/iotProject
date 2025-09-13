#include <Arduino.h>


#include "SystemState.h"

#include <vector>
#include <string>
#include "WiFiManager.h"
#include "PinoutData.h"
#include "Esp32_38pinBoard.h"
#include "Pin.h"

const char *ssid = "YOUT_PREFERRED_WIFI_SSID";
const char *password = "YOUT_PREFERRED_WIFI_PW";

SystemState *systemState;

PinoutData *pinoutData;

/**
 * For the correct usage of this project you MUST install all library present on ./Library
 * You can do it directly fron Arduino ide creating the zip of each subfolder present in ./Library
 * and manually imported it:  Sketch ->include Library -> Add .zip library
 * Or: copy All on your Arduino library installation folder,
 * Default installation folder for arduino on Arch based Distro: ~/Arduino/libraries/
 */

void setup()
{
  Serial.begin(9600);
  
  try
  {
    systemState = SystemState::getInstance();
    /**
     *
     * pinoutData = new Esp32_38pin(); //pinout esp scollegato dalla board!
     * selezionare la tipologia corretta in base al microconntrolore utilizzato!
     * E' possibile crearne uno custom come fatto ad esempio qui sotto
     */
    pinoutData = new Esp32_38pinBoard();
    systemState->setPinoutData(pinoutData);
    /**
     * Se si vuole utilizzare modalita preferenziale connesso a una rete wifi
     * decommentare questa riga e commentare quella sotto
     */
    //WiFiManager *wifiManager = new WiFiManager(ssid, password);
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
