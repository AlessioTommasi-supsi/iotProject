#ifndef VIEWADSHISTORY_H
#define VIEWADSHISTORY_H

#include <Arduino.h>
#include "viewGeneric.h"
#include "SystemState.h"

class viewADSHistory {
public:
    static String generateHTML();
    static String adsContent();
private:
    static String html;
};

#endif // VIEWADSHISTORY_H
