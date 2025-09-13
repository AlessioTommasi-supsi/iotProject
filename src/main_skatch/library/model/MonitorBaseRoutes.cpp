#include "MonitorBaseRoutes.h"
#include "viewGraph.h"
#include "viewGeneric.h"
#include "SystemState.h"
#include "PinoutData.h"

String MonitorBaseRoutes::generateCommonMonitorCSS()
{
    String css = "<style>";
    css += ".monitor-section { margin: 30px 0; }";
    css += ".monitor-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; margin: 20px 0; }";
    css += ".monitor-card { background: rgba(255, 255, 255, 0.9); border-radius: 15px; padding: 20px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }";
    css += ".monitor-value { font-size: 24px; font-weight: bold; color: #2196F3; }";
    css += ".monitor-label { font-size: 14px; color: #666; margin-bottom: 5px; }";
    css += ".status-ok { color: #4CAF50; }";
    css += ".status-warning { color: #FF9800; }";
    css += ".status-critical { color: #f44336; }";
    css += ".progress-bar { width: 100%; height: 20px; background: #e0e0e0; border-radius: 10px; overflow: hidden; margin: 10px 0; }";
    css += ".progress-fill { height: 100%; background: linear-gradient(90deg, #4CAF50, #FF9800, #f44336); transition: width 0.3s ease; }";
    css += ".section-divider { border-top: 2px solid #e0e0e0; margin: 40px 0 20px 0; padding-top: 20px; }";
    css += "</style>";
    return css;
}

String MonitorBaseRoutes::generateCommonMonitorScript()
{
    String script = "<script>";
    script += "function updateSystemMonitor() {";
    script += "  fetch('/systemStats')";
    script += "    .then(response => response.json())";
    script += "    .then(data => {";
    script += "      const grid = document.getElementById('systemMonitorGrid');";
    script += "      if (grid) { grid.innerHTML = ''; updateMonitorCards(data); }";
    script += "    })";
    script += "    .catch(error => console.error('Monitor update error:', error));";
    script += "}";
    script += "</script>";
    return script;
}

void MonitorBaseRoutes::addCORSHeaders(AsyncWebServerResponse* response)
{
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Cache-Control", "no-cache");
}