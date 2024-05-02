#include <Arduino.h>
#include "model/Led.cpp"

const int LedPin = 13; // Pin del Led

void setup()
{
  //prova
  // Inizializzazione del Led
  Led Led(LedPin);
  Led.blink(2);    // Lampeggia il Led due volte al secondo
  delay(5000);    // Attendi per 10 secondi
  Led.stopBlink(); // Interrompi il lampeggio del Led
}

void loop()
{
  // Non c'è bisogno di implementare nulla qui perché il programma termina dopo 10 secondi
}
