#include "monitorResource.h"

void MonitorResource::defineRoutes(AsyncWebServer &server)
{
    // Delega la definizione delle route alle classi specializzate
    // Ogni classe gestisce la propria responsabilità specifica
    
    // UI principale del monitor (/monitor, /monitorPinStack, etc.)
    uiRoutes.defineRoutes(server);
    
    // Statistiche di sistema (/systemStats, /monitorHeapData)
    statsRoutes.defineRoutes(server);
    
    // Informazioni sui task (/taskInfo)
    taskRoutes.defineRoutes(server);
    
    // Ottimizzazione heap (/optimizeHeap)
    heapRoutes.defineRoutes(server);
    
    // Monitor avanzato (/systemMonitor)
    systemRoutes.defineRoutes(server);
}
