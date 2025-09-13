#ifndef VIEWPINHISTORY_H
#define VIEWPINHISTORY_H

#include <Arduino.h>
#include "viewGeneric.h"
#include "SystemState.h"

class viewPinHistory {
public:
    static String generateHTML();
    static String pinContent();
private:
    static String html;
};

#endif // VIEWPINHISTORY_H