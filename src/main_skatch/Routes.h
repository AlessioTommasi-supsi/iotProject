#ifndef ROUTES_H
#define ROUTES_H

#include <ESPAsyncWebSrv.h>
#include <Arduino.h>
#include "viewCurrentRegister.h"
#include "viewHistory.h"
#include "viewGraph.h"
//#include "WiFiManager.h"
#include "SystemState.h"



class Routes
{
public:
    static void defineRoutes(AsyncWebServer &server);
};

#endif // ROUTES_H