#ifndef ADS1115_MODEL_H
#define ADS1115_MODEL_H

#include <Arduino.h>
#include "Pin.h"

// Definizione dei pin del multiplexer (collegati all'ESP32)
#define PIN_A 12  // S0 MUX
#define PIN_B 13  // S1 MUX
#define PIN_C 14  // S2 MUX

class ADS1115_model {
public:
    // Imposta il canale del multiplexer (mappa completa da 0 a 7)
    static void setChannel(int channel);
};
#endif // ADS1115_MODEL_H
