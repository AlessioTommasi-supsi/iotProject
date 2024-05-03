#include <Arduino.h>
#include "LedEsp32.h"
#include "WifiManager.h"
#include "WebServer.h"

LedEsp32 *led;
WiFiManager* wifiManager;

WebServer server;

void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    ; // Attendi finché la porta seriale non è pronta
  }
  
  Serial.println("La porta seriale è pronta! Hello, world!");

  led = new LedEsp32(13);
  wifiManager = new WiFiManager();
  server.begin();

  led->blink(2);
  delay(5000);
  led->stopBlink();
  led->turnOn();
  delay(50000);
  led->turnOff();

  destroy();
}

void destroy()
{
  // Deallocazione della memoria
  server.stop();
  delete wifiManager;
  delete led;
}


void loop()
{
  // Non c'è bisogno di implementare nulla qui perché il programma termina dopo 10 secondi
}
