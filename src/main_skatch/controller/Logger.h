#ifndef LOGGER_H
#define LOGGER_H

#include <SPI.h>
#include <SD.h>

class SystemState;

class Logger {
public:
    static Logger& getInstance();
    void begin(int chipSelectPin);
    void log(const String& data);
    void close();

private:
    Logger(); // Costruttore privato
    Logger(const Logger&) = delete; // Disabilita copia
    Logger& operator=(const Logger&) = delete; // Disabilita assegnazione
    File myFile;
    bool initialized = false;
};

#endif
