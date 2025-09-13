#ifndef MONITORBASEROUTES_H
#define MONITORBASEROUTES_H

#include "RoutesInterface.h"
#include <ESPAsyncWebSrv.h>
#include <Arduino.h>

// Include comuni essenziali - rimosso SystemState per evitare inclusioni circolari
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <esp_heap_caps.h>

#ifdef ESP32
#include <esp_task_wdt.h>
#include <WiFi.h>
#endif

// Forward declarations invece degli include
class SystemState;
class PinoutData;

/**
 * @brief Classe base per tutte le route di monitoring
 * Fornisce funzionalità comuni e utility condivise
 */
class MonitorBaseRoutes : public RoutesInterface
{
protected:
    // Utility methods condivise
    String generateCommonMonitorCSS();
    String generateCommonMonitorScript();
    void addCORSHeaders(AsyncWebServerResponse* response);
    
public:
    virtual void defineRoutes(AsyncWebServer &server) = 0;
};

#endif // MONITORBASEROUTES_H