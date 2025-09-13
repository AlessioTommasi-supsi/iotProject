#ifndef SYSTEMSTATSROUTES_H
#define SYSTEMSTATSROUTES_H

#include "MonitorBaseRoutes.h"

/**
 * @brief Gestisce gli endpoint per le statistiche di sistema e metriche
 * Responsabilità: fornire dati JSON per heap, PSRAM, CPU, WiFi, FreeRTOS
 */
class SystemStatsRoutes : public MonitorBaseRoutes
{
private:
    String generateSystemStatsJSON();
    String generateHeapStatsJSON();
    String generatePSRAMStatsJSON();
    String generateFreeRTOSStatsJSON();
    String generateSystemInfoJSON();
    String generateWiFiStatsJSON();
    
public:
    void defineRoutes(AsyncWebServer &server) override;
};

#endif // SYSTEMSTATSROUTES_H