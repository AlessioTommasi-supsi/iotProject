#ifndef ESP32_38PIN_H
#define ESP32_38PIN_H

#include "PinoutData.h"

class Esp32_38pin : public PinoutData {
private:
    

public:
    std::vector<Pin> pins;
    Esp32_38pin();

    void printPinsOnSerial() override;
    void initializePins() override;
    void readPins() override;
    void addPin(const Pin& pin) override;
    Pin& getPin(int GPIOPin) override;
    std::vector<Pin> getPins() override;
    std::vector<int> getPinNumbers() override;
    std::vector<Pin>::iterator begin() override;
    std::vector<Pin>::iterator end() override;
    std::vector<Pin>::const_iterator begin() const override;
    std::vector<Pin>::const_iterator end() const override;

    std::string toString() const override;
    void savePinsToMemory() override;
    void savePinToMemory(int pinNumber);
};

#endif // ESP32_38PIN_H
