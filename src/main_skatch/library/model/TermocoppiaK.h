#ifndef TERMOCOPPIA_K_H
#define TERMOCOPPIA_K_H

#include <Arduino.h>

class TermocoppiaK {
private:
    // Struttura per memorizzare i punti della tabella di calibrazione
    struct CalibrationPoint {
        float temperature;  // Temperatura in °C
        float voltage;      // Tensione in mV
    };
    
    // Tabella di calibrazione IEC 584-1 per termocoppia tipo K
    static const CalibrationPoint calibrationTable[];
    static const int tableSize;
    
    // Metodo per interpolazione lineare tra due punti della tabella
    float interpolate(float voltage) const;
    
public:
    TermocoppiaK();
    ~TermocoppiaK();
    
    // Metodo per ottenere la temperatura dato un valore in mV
    // Input: tensione in mV
    // Output: temperatura in °C
    float getTemperature(float millivolts);
    
    // Metodo per validare se la tensione è nel range della tabella
    bool isValidVoltage(float millivolts) const;
    
    // Fattore di correzione per convertire microV in mV (simile al caso 3)
    static const float CORRECTION_FACTOR;
    
    // Costanti di errore
    static const float ERROR_VALUE;
    static const float MIN_TEMP;
    static const float MAX_TEMP;
};

#endif // TERMOCOPPIA_K_H