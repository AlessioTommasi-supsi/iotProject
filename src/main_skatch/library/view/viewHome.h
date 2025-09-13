#ifndef viewHome_h
#define viewHome_h

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include "SystemState.h"

class viewHome
{
private:
public:
    static String html;
    static String generateHTML();
    static String pageContent();
};

#endif