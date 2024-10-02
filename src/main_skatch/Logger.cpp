#include "Logger.h"
#include "SystemState.h"

Logger::Logger() {
    // Costruttore privato
}

Logger& Logger::getInstance() {
    static Logger instance; // Istanza singleton
    return instance;
}

void Logger::begin(int chipSelectPin) {
    if (!initialized) {
        if (!SD.begin(chipSelectPin)) {
            const char* errorMessage = "Errore nell'inizializzazione della scheda SD!";
            Serial.println(errorMessage);
            SystemState::getInstance()->setError(const_cast<char*>(errorMessage));
            return;
        }
        Serial.println("Scheda SD inizializzata.");
        myFile = SD.open("log.txt", FILE_WRITE);
        if (myFile) {
            Serial.println("File aperto con successo.");
            initialized = true;
        } else {
            Serial.println("Errore nell'apertura del file.");
        }
    }
}

void Logger::log(const String& data) {
    if (initialized && myFile) {
        myFile.print(data);
        myFile.flush(); // Assicura che i dati siano scritti su SD
        Serial.print("Dati scritti: ");
        Serial.println(data);
    }
}

void Logger::close() {
    if (myFile) {
        myFile.close();
        Serial.println("File chiuso.");
    }
}
