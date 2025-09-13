#ifndef PT1000_H
#define PT1000_H

#include <Arduino.h>

class PT1000 {
private:
    // Struttura per memorizzare i punti della tabella di calibrazione
    struct CalibrationPoint {
        float resistance; // Resistenza in Ohm
        float temperature; // Temperatura in °C
    };
    
    // Tabella di calibrazione IEC 751 per PT1000
    // Relazione Resistenza (Ohm) → Temperatura (°C)
    static const CalibrationPoint calibrationTable[];
    static const int tableSize;
    
    // Metodo per interpolazione lineare tra due punti della tabella
    float interpolate(float resistance) const;
    
public:
    PT1000();
    ~PT1000();
    
    // Metodo per ottenere la temperatura data una resistenza in Ohm
    // Input: resistenza in Ohm
    // Output: temperatura in °C
    float getTemperature(float resistance);
    
    // Metodo per validare se la resistenza è nel range della tabella
    bool isValidResistance(float resistance) const;
    
    // Costanti di errore e range
    static const float ERROR_VALUE;
    static const float MIN_RESISTANCE;
    static const float MAX_RESISTANCE;
    static const float MIN_TEMP;
    static const float MAX_TEMP;
};

#endif // PT1000_H