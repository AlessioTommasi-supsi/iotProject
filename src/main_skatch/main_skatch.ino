#include <Arduino.h>
#include "LedEsp32.h"
#include "WifiManager.h"

LedEsp32 *led;
WiFiManager* wifiManager;

void setup()
{
  Serial.begin(115200); // Imposta il baud rate a 115200 (puoi modificare il valore a seconda delle tue esigenze)

  // Attendere che la porta seriale sia pronta
  while (!Serial) {
    ; // Attendi finché la porta seriale non è pronta
  }
  
  // Ora la porta seriale è pronta e possiamo inviare messaggi
  Serial.println("La porta seriale è pronta! Hello, world!");


  // Inizializzazione del LedEsp32
  led = new LedEsp32(13);
  wifiManager = new WiFiManager();
  
  // Accensione del LedEsp32
  /*
  LedEsp32.turnOn();
  delay(500);
  LedEsp32.turnOff();
  delay(500);
  LedEsp32.turnOn();
  delay(500);
  LedEsp32.turnOff();
  delay(500);
  LedEsp32.turnOn();
  */
  

  led->blink(2);
  delay(5000);
  led->stopBlink();
  led->turnOn();
  delay(50000);
  led->turnOff();
  distroy();
}

void distroy()
{
  // Deallocazione della memoria
  delete wifiManager;
  delete led;
}


void loop()
{
  // Non c'è bisogno di implementare nulla qui perché il programma termina dopo 10 secondi
}
