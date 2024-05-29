#ifndef ROUTES_H
#define ROUTES_H

#include <ESPAsyncWebSrv.h>
#include <Arduino.h>
#include "viewCurrentRegister.h"

class Routes
{
public:
    static void defineRoutes(AsyncWebServer &server);
};

#endif // ROUTES_H