#ifndef VIEWMODBUSHISTORY_H
#define VIEWMODBUSHISTORY_H

#include <Arduino.h>
#include "viewGeneric.h"
#include "SystemState.h"

class viewModbusHistory {
public:
    static String generateHTML();
    static String modbusContent();
private:
    static String html;
};

#endif // VIEWMODBUSHISTORY_H