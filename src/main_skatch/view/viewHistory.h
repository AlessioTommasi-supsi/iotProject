#ifndef viewHistory_H
#define viewHistory_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include "SystemState.h"

class viewHistory
{
private:
public:
    static String html;
    static String generateHTML();
};

#endif