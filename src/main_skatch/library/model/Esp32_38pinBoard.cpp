#include "Esp32_38pinBoard.h"

Esp32_38pinBoard::Esp32_38pinBoard() {
    Serial.println("Costruttore Esp32_38pinBoard");
    initializePins();
    printPinsOnSerial();
    Serial.println("Inizializzazione Esp32_38pinBoard effettuata!");
}

/**
 * di default seleziono il canale 0 del MUX!
 */
void Esp32_38pinBoard::initializePins()
{
    // NON chiamare Esp32_38pin::initializePins() perché è già chiamato nel costruttore del padre
    
    // Modifica i pin specifici per questa board
    // getPin() restituisce il riferimento al pin esistente se presente
    Pin &pinA = getPin(12);
    pinA.setNote("MUX S0 - A");
    pinA.setPinType(PinType::DIGITAL);
    pinA.setIsInput(false); // Imposta come output
    pinA.write(false);

    Pin &pinB = getPin(13);
    pinB.setNote("MUX S1 - B");
    pinB.setPinType(PinType::DIGITAL);
    pinB.setIsInput(false); // Imposta come output
    pinB.write(false);

    Pin &pinC = getPin(14);
    pinC.setNote("MUX S2 - C");
    pinC.setPinType(PinType::DIGITAL);
    pinC.setIsInput(false); // Imposta come output
    pinC.write(false);        
}