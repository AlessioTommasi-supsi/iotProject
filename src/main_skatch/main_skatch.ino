#include <Arduino.h>
#include "./LedEsp32.h"

const int LedEsp32Pin = 13; // Pin del LedEsp32

void setup()
{
  // Inizializzazione del LedEsp32
  LedEsp32 led(LedEsp32Pin);

  // Accensione del LedEsp32
  led.turnOn();
  delay(500);
  led.turnOff();
  delay(500);
  led.turnOn();
  delay(500);
  led.turnOff();
  delay(500);
  led.turnOn();
}

void loop()
{
  // Non c'è bisogno di implementare nulla qui perché il programma termina dopo 10 secondi
}
