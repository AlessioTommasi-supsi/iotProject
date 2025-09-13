#ifndef PINOUTDATA_H
#define PINOUTDATA_H

#include <vector>
#include <string>
#include "Pin.h"

class PinoutData {
public:
    virtual ~PinoutData() = default;

    virtual void initializePins() = 0;
    virtual void printPinsOnSerial() = 0;
    virtual void readPins() = 0;
    virtual void addPin(const Pin& pin) = 0;
    virtual Pin& getPin(int GPIOPin) = 0;
    virtual std::vector<Pin> getPins() = 0;
    virtual std::vector<int> getPinNumbers() = 0;
    virtual std::vector<Pin>::iterator begin() = 0;
    virtual std::vector<Pin>::iterator end() = 0;
    virtual std::vector<Pin>::const_iterator begin() const = 0;
    virtual std::vector<Pin>::const_iterator end() const = 0;
    virtual std::string toString() const = 0;
    virtual void savePinsToMemory() = 0;
    virtual void savePinToMemory(int pinNumber) = 0;
};

#endif // PINOUTDATA_H
