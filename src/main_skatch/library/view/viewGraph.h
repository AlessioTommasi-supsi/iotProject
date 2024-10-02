#ifndef viewGraph_H
#define viewGraph_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include <set> 
#include "SystemState.h"

class viewGraph
{
private:
public:
    static String html;
    static String generateHTML();
};

#endif