#ifndef PINOUTROUTES_H
#define PINOUTROUTES_H

#include "RoutesInterface.h"
#include <ESPAsyncWebSrv.h>
#include <Arduino.h>
#include <vector>
#include <string>

#include "pinout.h"
#include "viewGraph.h"
#include "viewGeneric.h"
#include "viewEditPin.h"
#include "viewPinHistory.h"
#include "viewCurrentRegister.h"
#include "viewHistory.h"

#include "SystemState.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>



class pinoutRoutes : public RoutesInterface
{
public:
    void defineRoutes(AsyncWebServer &server);
};

#endif // PINOUTROUTES_H
