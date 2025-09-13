#ifndef SYSTEMMONITORROUTES_H
#define SYSTEMMONITORROUTES_H

#include "MonitorBaseRoutes.h"

/**
 * @brief Gestisce la pagina avanzata di monitoraggio sistema
 * Responsabilità: endpoint /systemMonitor con layout avanzato e funzionalità complete
 */
class SystemMonitorRoutes : public MonitorBaseRoutes
{
private:
    String generateAdvancedMonitorPage();
    String generateAdvancedMonitorScript();
    
public:
    void defineRoutes(AsyncWebServer &server) override;
};

#endif // SYSTEMMONITORROUTES_H