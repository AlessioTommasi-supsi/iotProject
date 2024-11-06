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
  
  try
  {
    // Disabilita il task watchdog 
    /* questa da errori sul seriale stampa: E: esp_task_wdt_reset non dichiarato
    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = 0, // 0 per disabilitare
        .idle_core_mask = 0, // Disabilita il watchdog per entrambi i core
        .trigger_panic = false // Non attivare il panic handler
    };
    esp_task_wdt_init(&wdt_config); // Passa la configurazione alla funzione

    esp_task_wdt_delete(xTaskGetIdleTaskHandleForCPU(0)); // Disabilita il watchdog per il core 0
    esp_task_wdt_delete(xTaskGetIdleTaskHandleForCPU(1)); // Disabilita il watchdog per il core 1
    esp_task_wdt_delete(NULL);
    */
    // Disabilita il watchdog RTC
    /*non funziona
    rtc_wdt_protect_off();
    rtc_wdt_disable();
    */
    systemState = SystemState::getInstance();
    // Initialize the SlaveModbus with the correct pins
    
    masterModbus = new MasterModbus();
    //WiFiManager *wifiManager = new WiFiManager(ssid, password); // per comodita versione finale usa quello sotto
    WiFiManager *wifiManager = new WiFiManager();

    systemState->setWifiManager(wifiManager);

    slaveModbus = new SlaveModbus(32, 33);
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
