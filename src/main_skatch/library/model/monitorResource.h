#ifndef MONITORRESOURCE_H
#define MONITORRESOURCE_H

#include "RoutesInterface.h"
#include <ESPAsyncWebSrv.h>

// Include delle nuove classi modulari
#include "MonitorUIRoutes.h"
#include "SystemStatsRoutes.h"
#include "TaskInfoRoutes.h"
#include "HeapOptimizationRoutes.h"
#include "SystemMonitorRoutes.h"

/**
 * @brief Classe principale che coordina tutte le route di monitoring
 * Implementa il pattern Composite per gestire le sottoclassi specializzate
 * Responsabilità: coordinamento e delega alle classi specifiche
 */
class MonitorResource : public RoutesInterface
{
private:
    // Istanze delle classi specializzate
    MonitorUIRoutes uiRoutes;
    SystemStatsRoutes statsRoutes;
    TaskInfoRoutes taskRoutes;
    HeapOptimizationRoutes heapRoutes;
    SystemMonitorRoutes systemRoutes;

public:
    void defineRoutes(AsyncWebServer &server) override;
};

#endif // MONITORRESOURCE_H