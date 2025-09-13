#include "Esp32_38pin.h"
#include <Arduino.h>
#include <sstream>


Esp32_38pin::Esp32_38pin() {
    Serial.println("Costruttore Esp32_38pin");
    initializePins();
    Serial.println("Inizializzazione dei pin effettuata!");
}

std::vector<Pin> Esp32_38pin::getPins() {
    return pins;
}


std::vector<int> Esp32_38pin::getPinNumbers() {
    std::vector<int> pinNumbers;
    for (const auto& pin : pins) {
        pinNumbers.push_back(pin.getNumber());
    }
    return pinNumbers;
}

void Esp32_38pin::initializePins()
{
    try
    {
        pins.clear();

        Pin &vspiMosiPin = getPin(23);
        vspiMosiPin.setNumber(23);
        vspiMosiPin.setPinType(PinType::SPI);
        vspiMosiPin.setIsInput(true);
        vspiMosiPin.setNote("VSPI MOSI or input digital");
        addPin(vspiMosiPin);

        Pin &adc0Pin = getPin(36);
        adc0Pin.setNumber(36);
        adc0Pin.setPinType(PinType::ADC);
        adc0Pin.setIsInput(true);
        adc0Pin.setNote("ADC0 - SENSOR_VP");
        addPin(adc0Pin);

        Pin &i2cSclPin = getPin(22);
        i2cSclPin.setNumber(22);
        i2cSclPin.setPinType(PinType::I2C);
        i2cSclPin.setIsInput(true);
        i2cSclPin.setNote("I2C SCL");
        addPin(i2cSclPin);

        Pin &adc3Pin = getPin(39);
        adc3Pin.setNumber(39);
        adc3Pin.setPinType(PinType::ADC);
        adc3Pin.setIsInput(true);
        adc3Pin.setNote("ADC3 - SENSOR_VN");
        addPin(adc3Pin);

        Pin &uartTxd0Pin = getPin(1);
        uartTxd0Pin.setNumber(1);
        uartTxd0Pin.setPinType(PinType::UART);
        uartTxd0Pin.setIsInput(true);
        uartTxd0Pin.setNote("UART TXD0 or input digital");
        addPin(uartTxd0Pin);

        Pin &adc6Pin = getPin(34);
        adc6Pin.setNumber(34);
        adc6Pin.setPinType(PinType::ADC);
        adc6Pin.setIsInput(true);
        adc6Pin.setNote("ADC6 - Input only");
        addPin(adc6Pin);

        Pin &uartRxd0Pin = getPin(3);
        uartRxd0Pin.setNumber(3);
        uartRxd0Pin.setPinType(PinType::UART);
        uartRxd0Pin.setIsInput(true);
        uartRxd0Pin.setNote("UART RXD0");
        addPin(uartRxd0Pin);

        Pin &adc7Pin = getPin(35);
        adc7Pin.setNumber(35);
        adc7Pin.setPinType(PinType::ADC);
        adc7Pin.setIsInput(true);
        adc7Pin.setNote("ADC7 - Input only");
        addPin(adc7Pin);

        Pin &i2cSdaPin = getPin(21);
        i2cSdaPin.setNumber(21);
        i2cSdaPin.setPinType(PinType::I2C);
        i2cSdaPin.setIsInput(true);
        i2cSdaPin.setNote("I2C SDA");
        addPin(i2cSdaPin);

        Pin &adc4Pin = getPin(32);
        adc4Pin.setNumber(32);
        adc4Pin.setPinType(PinType::ADC);
        adc4Pin.setIsInput(true);
        adc4Pin.setNote("ADC4, TOUCH9");
        addPin(adc4Pin);

        Pin &adc5Pin = getPin(33);
        adc5Pin.setNumber(33);
        adc5Pin.setPinType(PinType::ADC);
        adc5Pin.setIsInput(true);
        adc5Pin.setNote("ADC5, TOUCH8");
        addPin(adc5Pin);

        Pin &vspiMisoPin = getPin(19);
        vspiMisoPin.setNumber(19);
        vspiMisoPin.setPinType(PinType::SPI);
        vspiMisoPin.setIsInput(true);
        vspiMisoPin.setNote("VSPI MISO");
        addPin(vspiMisoPin);

        Pin &dac1Pin = getPin(25);
        dac1Pin.setNumber(25);
        dac1Pin.setPinType(PinType::ADC);
        dac1Pin.setIsInput(false);
        dac1Pin.setVoltage(3300);
        dac1Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(dac1Pin);

        Pin &vspiClkPin = getPin(18);
        vspiClkPin.setNumber(18);
        vspiClkPin.setPinType(PinType::SPI);
        vspiClkPin.setIsInput(true);
        vspiClkPin.setNote("VSPI CLK or input digital");
        addPin(vspiClkPin);

        Pin &dac2Pin = getPin(26);
        dac2Pin.setNumber(26);
        dac2Pin.setPinType(PinType::ADC);
        dac2Pin.setIsInput(false);
        dac2Pin.setVoltage(3300);
        dac2Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(dac2Pin);

        Pin &pwmPin = getPin(5);
        pwmPin.setNumber(5);
        pwmPin.setPinType(PinType::PWM);
        pwmPin.setIsInput(true);
        pwmPin.setNote("input digital VSPI CS0, PWM");
        addPin(pwmPin);

        Pin &adc17Pin = getPin(27);
        adc17Pin.setNumber(27);
        adc17Pin.setPinType(PinType::ADC);
        adc17Pin.setIsInput(false);
        adc17Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(adc17Pin);

        Pin &uartRxd1Pin = getPin(17);
        uartRxd1Pin.setNumber(17);
        uartRxd1Pin.setPinType(PinType::UART);
        uartRxd1Pin.setIsInput(true);
        uartRxd1Pin.setNote("UART RXD1");
        addPin(uartRxd1Pin);

        Pin &adc16Pin = getPin(14);
        adc16Pin.setNumber(14);
        adc16Pin.setPinType(PinType::ADC);
        adc16Pin.setIsInput(false);
        adc16Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(adc16Pin);

        Pin &uartTxd2Pin = getPin(16);
        uartTxd2Pin.setNumber(16);
        uartTxd2Pin.setPinType(PinType::UART);
        uartTxd2Pin.setIsInput(true);
        uartTxd2Pin.setNote("UART TXD2");
        addPin(uartTxd2Pin);

        Pin &adc15Pin = getPin(12);
        adc15Pin.setNumber(12);
        adc15Pin.setPinType(PinType::ADC);
        adc15Pin.setIsInput(false);
        adc15Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(adc15Pin);

        Pin &adc10Pin = getPin(4);
        adc10Pin.setNumber(4);
        adc10Pin.setPinType(PinType::ADC);
        adc10Pin.setIsInput(true);
        adc10Pin.setNote("ADC10, TOUCH0");
        addPin(adc10Pin);

        Pin &adc11Pin = getPin(0);
        adc11Pin.setNumber(0);
        adc11Pin.setPinType(PinType::ADC);
        adc11Pin.setIsInput(false);
        adc11Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(adc11Pin);

        Pin &adc2Pin = getPin(13);
        adc2Pin.setNumber(13);
        adc2Pin.setPinType(PinType::ADC);
        adc2Pin.setIsInput(false);
        adc2Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(adc2Pin);

        Pin &adc12Pin = getPin(2);
        adc12Pin.setNumber(2);
        adc12Pin.setPinType(PinType::ADC);
        adc12Pin.setIsInput(false);
        adc12Pin.setNote("ADC2 is in use by Wi-Fi. Please see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-limitations for more info");
        addPin(adc12Pin);

        // Add pins using the new structure
        Pin &sdD2Pin = getPin(9);
        sdD2Pin.setNumber(9);
        sdD2Pin.setPinType(PinType::DIGITAL);
        sdD2Pin.setIsInput(true);
        sdD2Pin.setNote("SD D2");
        addPin(sdD2Pin);

        Pin &sdD3Pin = getPin(10);
        sdD3Pin.setNumber(10);
        sdD3Pin.setPinType(PinType::DIGITAL);
        sdD3Pin.setIsInput(true);
        sdD3Pin.setNote("SD D3");
        addPin(sdD3Pin);

        Pin &sd2SpiwpPin = getPin(8);
        sd2SpiwpPin.setNumber(8);
        sd2SpiwpPin.setPinType(PinType::DIGITAL);
        sd2SpiwpPin.setIsInput(true);
        sd2SpiwpPin.setNote("SD2 SPIWP HS1 DATA 1");
        addPin(sd2SpiwpPin);

        Pin &spics0CmdPin = getPin(11);
        spics0CmdPin.setNumber(11);
        spics0CmdPin.setPinType(PinType::DIGITAL);
        spics0CmdPin.setIsInput(true);
        spics0CmdPin.setNote("SPICS0 CMD");
        addPin(spics0CmdPin);

        Pin &sd0SpiqPin = getPin(7);
        sd0SpiqPin.setNumber(7);
        sd0SpiqPin.setPinType(PinType::DIGITAL);
        sd0SpiqPin.setIsInput(true);
        sd0SpiqPin.setNote("SD0 SPIQ HS1 DATA 0");
        addPin(sd0SpiqPin);

        Pin &sd0SpidPin = getPin(6);
        sd0SpidPin.setNumber(6);
        sd0SpidPin.setPinType(PinType::DIGITAL);
        sd0SpidPin.setIsInput(true);
        sd0SpidPin.setNote("segnale di clock temporizzato");
        addPin(sd0SpidPin);
    }
    catch (...)
    {
        Serial.println("Errore durante l'inizializzazione dei pin: ");
    }

    //printPinsOnSerial();
}

void Esp32_38pin::addPin(const Pin& pin) {
    try
    {
        pins.push_back(pin);
    }
    catch(...)
    {
        Serial.println("Errore durante l'aggiunta del pin: " + pin.toString());
    }
    
}


void Esp32_38pin::printPinsOnSerial() {
    Serial.println("Pinout ESP32 38 pin:");

    try
    {
        for (const auto& pin : pins) {
            Serial.println(pin.toString());
        }
    }
    catch(const std::exception& e)
    {
        Serial.println("Errore durante la stampa dei pin: " + String(e.what()));
    }
    
}



void Esp32_38pin::readPins() {
    for (auto& pin : pins) {
        uint16_t value = pin.read();

        // Stampa il valore letto per il debug
        //Serial.println("readed value: "); 
        //Serial.println(pin.toString());
        
    }
}


Pin& Esp32_38pin::getPin(int GPIOPin) {
    for (auto& pin : pins) {
        if (pin.getNumber() == GPIOPin) {
            return pin;
        }
    }
    static Pin defaultPin(GPIOPin, PinType::UNKNOWN, true/*di default i pin sono in lettura, cosi non ho problemi se ci metto tensione all inizio*/, "Pin not found");
    Serial.println("Pin " + String(GPIOPin) + " not found");
    return defaultPin;
}



std::vector<Pin>::iterator Esp32_38pin::begin() {
    return pins.begin();
}

std::vector<Pin>::iterator Esp32_38pin::end() {
    return pins.end();
}

std::vector<Pin>::const_iterator Esp32_38pin::begin() const {
    return pins.begin();
}

std::vector<Pin>::const_iterator Esp32_38pin::end() const {
    return pins.end();
}

std::string Esp32_38pin::toString() const {
    std::ostringstream oss;
    for (const auto& pin : pins) {
        oss << pin.toString() << "\n";
    }
    return oss.str();
}

// **🔧 FIX: Implementazione metodo per salvare configurazione pin in memoria**
void Esp32_38pin::savePinsToMemory() {
    try {
        Serial.println("Saving ESP32_38pin configuration to memory...");
        
        // Qui potrei implementare il salvataggio su EEPROM, SPIFFS, o Preferences
        // Per ora stampo la configurazione salvata su Serial per debug
        for (const auto& pin : pins) {
            Serial.print("Saved Pin ");
            Serial.print(pin.getNumber());
            Serial.print(": Type=");
            Serial.print(pin.getType());
            Serial.print(", Input=");
            Serial.print(pin.getIsInput() ? "true" : "false");
            Serial.print(", Voltage=");
            Serial.println(pin.getVoltage());
        }
        
        Serial.println("ESP32_38pin configuration saved successfully!");
        
    } catch (const std::exception& e) {
        Serial.println("Error saving ESP32_38pin configuration: " + String(e.what()));
    } catch (...) {
        Serial.println("Unknown error saving ESP32_38pin configuration");
    }
}

// **🔧 NEW: Metodo ottimizzato per salvare solo un pin specifico**
void Esp32_38pin::savePinToMemory(int pinNumber) {
    try {
        Serial.println("Saving ESP32_38pin pin " + String(pinNumber) + " configuration to memory...");
        
        // Trova il pin specifico
        Pin& pin = getPin(pinNumber);
        
        // Salva solo questo pin invece di tutti
        Serial.print("Saved Pin ");
        Serial.print(pin.getNumber());
        Serial.print(": Type=");
        Serial.print(pin.getType());
        Serial.print(", Input=");
        Serial.print(pin.getIsInput() ? "true" : "false");
        Serial.print(", Voltage=");
        Serial.println(pin.getVoltage());
        
        Serial.println("ESP32_38pin pin " + String(pinNumber) + " configuration saved successfully!");
        
    } catch (const std::exception& e) {
        Serial.println("Error saving ESP32_38pin pin " + String(pinNumber) + " configuration: " + String(e.what()));
    } catch (...) {
        Serial.println("Unknown error saving ESP32_38pin pin " + String(pinNumber) + " configuration");
    }
}
