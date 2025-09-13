#ifndef MONITORUIROUTES_H
#define MONITORUIROUTES_H

#include "MonitorBaseRoutes.h"

/**
 * @brief Gestisce la pagina principale del monitor e le route UI
 * Responsabilità: rendering della pagina monitor principale con grafici e interfaccia
 */
class MonitorUIRoutes : public MonitorBaseRoutes
{
private:
    String generateMainMonitorPage();
    String generateMonitorButtons();
    String generateSystemStatsSection();
    String generateHeapMonitorSection();
    String generateStackUsageSection();
    String generateMonitorJavaScript();
    
public:
    void defineRoutes(AsyncWebServer &server) override;
};

#endif // MONITORUIROUTES_H