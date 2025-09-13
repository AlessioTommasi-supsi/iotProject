#ifndef ESP32_30PIN_H
#define ESP32_30PIN_H

#include "PinoutData.h"

/************************************************************************
 * Pin ADC2 (GPIO da 12 a 15, 25, 26, 27):                              *
 * Non utilizzare per letture analogiche durante l'uso del Wi-Fi,       *
 * ma sono sicuri come output digitali.                                 *
 * Pin di Boot (GPIO 0, 2, 12): Prestare attenzione durante             *
 * il boot per evitare interferenze.                                    *
 **********************************************************************/

class Esp32_30pin : public PinoutData
{
private:
    std::vector<Pin> pins;

public:
    Esp32_30pin();

    void printPinsOnSerial() override;
    void initializePins() override;
    void readPins() override;
    void addPin(const Pin &pin) override;
    Pin &getPin(int GPIOPin) override;
    std::vector<Pin> getPins() override;
    std::vector<int> getPinNumbers() override;
    std::vector<Pin>::iterator begin() override;
    std::vector<Pin>::iterator end() override;
    std::vector<Pin>::const_iterator begin() const override;
    std::vector<Pin>::const_iterator end() const override;

    std::string toString() const override;
    void savePinsToMemory() override;
    void savePinToMemory(int pinNumber) override;
};

#endif // ESP32_38PIN_H
