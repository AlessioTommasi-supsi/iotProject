#include <Arduino.h>
#include "LedEsp32.h"

const int LedEsp32Pin = 13; // Pin del LedEsp32

void setup()
{
  // Inizializzazione del LedEsp32
  LedEsp32 LedEsp32(LedEsp32Pin);

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

  LedEsp32.blink(2);
  delay(5000);
  LedEsp32.stopBlink();
}

void loop()
{
  // Non c'è bisogno di implementare nulla qui perché il programma termina dopo 10 secondi
}
