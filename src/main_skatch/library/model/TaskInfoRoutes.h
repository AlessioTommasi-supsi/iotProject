#ifndef TASKINFOROUTES_H
#define TASKINFOROUTES_H

#include "MonitorBaseRoutes.h"

/**
 * @brief Gestisce le informazioni dettagliate sui task FreeRTOS
 * Responsabilità: pagina taskInfo e diagnostica dettagliata dei task
 */
class TaskInfoRoutes : public MonitorBaseRoutes
{
private:
    String generateTaskInfoPage();
    String generateTaskStatisticsSection();
    String generateSystemMemorySection();
    String generatePinTaskSection();
    String generateCPUInfoSection();
    
public:
    void defineRoutes(AsyncWebServer &server) override;
};

#endif // TASKINFOROUTES_H