#ifndef HEAPOPTIMIZATIONROUTES_H
#define HEAPOPTIMIZATIONROUTES_H

#include "MonitorBaseRoutes.h"

/**
 * @brief Gestisce l'ottimizzazione e pulizia dell'heap ESP32
 * Responsabilità: endpoint /optimizeHeap e tutte le operazioni di cleanup avanzate
 */
class HeapOptimizationRoutes : public MonitorBaseRoutes
{
private:
    // Operazioni di cleanup specifiche
    bool optimizeSystemState(String& errors);
    bool optimizeAsyncWebServer(String& errors);
    bool defragmentHeap(String& errors);
    bool cleanupCommunicationBuffers(String& errors);
    bool optimizeTaskWatchdog(String& errors);
    bool compactPSRAM(String& errors);
    bool cleanupFreeRTOSTasks(String& errors);
    bool garbageCollectStrings(String& errors);
    bool optimizeFlashMemory(String& errors);
    bool resetHeapStatistics(String& errors);
    
    String generateOptimizationResultJSON(bool success, size_t heapBefore, size_t heapAfter, const String& errors);
    
public:
    void defineRoutes(AsyncWebServer &server) override;
};

#endif // HEAPOPTIMIZATIONROUTES_H