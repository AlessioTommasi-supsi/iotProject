#ifndef PIN_H
#define PIN_H

#include "PinType.h"
#include <Arduino.h>
#include <vector>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class Pin
{
private:
    uint8_t number;   // Numero del pin
    PinType type;     // Tipo del pin
    uint16_t voltage; // Voltaggio in mV
    bool isInput;     // Flag per modalità input/output
    char note[200];   // Descrizione del pin

    size_t stackSize = 10000;            // Dimensione dello stack per il task in parole (1 parola = 4 byte)
    size_t timeToRecord = 1000;          // Tempo di registrazione in ms
    std::vector<uint16_t> valuesVoltage; // Valori registrati del voltaggio

    TaskHandle_t recordingTask = NULL; // Task per la registrazione
    
    // Mutex per thread safety
    mutable SemaphoreHandle_t mutex;

public:
    // Costruttore
    Pin(uint8_t num, PinType t, uint8_t input, const char *n, uint16_t volt = 0);
    
    // Distruttore
    ~Pin();
    
    // Copy constructor
    Pin(const Pin& other);
    
    // Assignment operator
    Pin& operator=(const Pin& other);

    // Equality operator for std::remove operations
    bool operator==(const Pin& other) const;

    // Getter e Setter thread-safe
    uint8_t getNumber() const;
    void setNumber(uint8_t num);
    
    PinType getPinType() const;
    void setPinType(PinType t);
    
    uint16_t getVoltage() const;
    void setVoltage(uint16_t volt);
    
    bool getIsInput() const;
    void setIsInput(bool input);
    
    void getNote(char* buffer, size_t bufferSize) const;
    void setNote(const char *newNote);
    
    size_t getStackSize() const;
    void setStackSize(size_t size);
    
    size_t getTimeToRecord() const;
    void setTimeToRecord(size_t time);
    
    TaskHandle_t getRecordingTask() const;

    // Metodi per configurazione e utilizzo del pin
    void setMode(uint8_t mode);
    bool write(bool goHigh);
    uint16_t read();
    void setType(String type);
    String getType() const;  // **🔧 FIX: Aggiungo const per permettere chiamate su oggetti const**

    // Metodi per la registrazione
    void startRecording(int milliseconds);
    void stopRecording();
    void recordingFunction();
    std::vector<float> getValuesVoltage();
    void editValue(int index, float value);
    void deleteValue(int index);

    // Metodi di utilità
    size_t getUsedStackInWords();
    size_t getStackSizeInWords();
    String toString() const;

    // Metodi statici per conversione
    static String pinTypeToString(PinType type);
    static PinType StringToPinType(String type);
};

#endif // PIN_H
