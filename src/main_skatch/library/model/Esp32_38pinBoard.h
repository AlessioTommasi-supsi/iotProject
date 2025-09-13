#ifndef ESP32_38PIN_BOARD_H
#define ESP32_38PIN_BOARD_H

#include "Esp32_38pin.h"

class Esp32_38pinBoard : public Esp32_38pin {
private:
    

public:
    std::vector<Pin> pins;
    Esp32_38pinBoard();

    void initializePins() override;
    
};

#endif // ESP32_38PIN_H
