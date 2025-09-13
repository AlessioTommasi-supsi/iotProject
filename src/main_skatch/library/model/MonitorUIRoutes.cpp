#include "MonitorUIRoutes.h"
#include "viewGraph.h"
#include "viewGeneric.h"
#include "SystemState.h"
#include "PinoutData.h"

void MonitorUIRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/monitor", HTTP_GET, [this](AsyncWebServerRequest *request){
        try
        {
            String htmlContent = generateMainMonitorPage();
            request->send(200, "text/html", htmlContent);
        }
        catch(...)
        {
            request->send(500, "text/html", "Monitor page error");
        }
    });

    server.on("/monitorPinStackDataContent", HTTP_GET, [](AsyncWebServerRequest *request){
        try
        {
            String htmlContent = "";
            PinoutData *pinoutData = SystemState::getInstance()->pinoutData;
            htmlContent += viewGraph::initCirularProgressBarGraph();

            for (auto pin = pinoutData->begin(); pin != pinoutData->end(); ++pin)
            {
                if (pin->getRecordingTask() != NULL)
                {
                    size_t stackUsed = pin->getUsedStackInWords() * 4;
                    size_t stackTotal = pin->getStackSizeInWords() * 4;
                    htmlContent += viewGraph::generateCirularProgressBarGraph("Pin" + String(pin->getNumber()) + "Stack", stackUsed, stackTotal, "/monitorPinStack?pin=" + String(pin->getNumber()), 1000);
                }
            }
            htmlContent += viewGraph::endCirularProgressBarGraph();
            request->send(200, "text/html", htmlContent);
        }
        catch(...)
        {
            request->send(500, "text/html", "Pin stack data error");
        }
    });

    server.on("/monitorPinStack", HTTP_GET, [](AsyncWebServerRequest *request){
        try
        {
            if (request->hasParam("pin"))
            {
                String pin = request->getParam("pin")->value();
                Pin &selectedPin = SystemState::getInstance()->pinoutData->getPin(pin.toInt());
                size_t stackUsed = selectedPin.getUsedStackInWords();
                size_t stackTotal = selectedPin.getStackSizeInWords();
                String json = "[" + String(stackUsed) + "," + String(stackTotal) + "]";
                request->send(200, "application/json", json);
            }
            else
            {
                String htmlContent = "";
                for (auto pin = SystemState::getInstance()->pinoutData->begin(); pin != SystemState::getInstance()->pinoutData->end(); ++pin)
                {
                    if (pin->getRecordingTask() != NULL)
                    {
                        size_t stackUsed = pin->getUsedStackInWords();
                        size_t stackTotal = pin->getStackSizeInWords();
                        htmlContent += viewGraph::generateCirularProgressBarGraph("Pin" + String(pin->getNumber()) + "Stack", stackUsed, stackTotal, "/monitorPinStack?pin=" + String(pin->getNumber()), 1000);
                    }
                }
                String fullHtml = viewGeneric::defaultCssHeader("Monitor Pin Stack");
                fullHtml += htmlContent;
                fullHtml += viewGeneric::defaultFooter();
                request->send(200, "text/html", fullHtml);
            }
        }
        catch (const std::exception &e)
        {
            Serial.println("Error: " + String(e.what()));
            request->send(500, "text/plain", "Internal Server Error");
        }
    });
}

String MonitorUIRoutes::generateMainMonitorPage()
{
    String htmlContent = viewGeneric::basicHeader("System Monitor");
    htmlContent += viewGeneric::addExportCSVScript();
    htmlContent += "<h1>🔍 System Monitor</h1>";
    htmlContent += generateCommonMonitorCSS();
    htmlContent += generateMonitorButtons();
    htmlContent += generateSystemStatsSection();
    htmlContent += generateHeapMonitorSection();
    htmlContent += generateStackUsageSection();
    htmlContent += generateMonitorJavaScript();
    htmlContent += viewGeneric::defaultFooter();
    return htmlContent;
}

String MonitorUIRoutes::generateMonitorButtons()
{
    String buttons = "<div style='text-align: center; margin: 20px 0;'>";
    buttons += "<button onclick=\"exportSystemData()\" style='background-color: #2196F3; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin: 0 5px;'>📊 Export System CSV</button>";
    buttons += "<button onclick=\"cleanupHeap()\" style='background-color: #f44336; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin: 0 5px;'>🧹 Cleanup Heap</button>";
    buttons += "<a href='/taskInfo' style='background-color: #FF9800; color: white; padding: 10px 20px; border: none; border-radius: 5px; text-decoration: none; margin: 0 5px;'>📋 Task Details</a>";
    buttons += "</div>";
    return buttons;
}

String MonitorUIRoutes::generateSystemStatsSection()
{
    String section = "<div class='monitor-section'>";
    section += "<h2>📊 System Statistics</h2>";
    section += "<div class='monitor-grid' id='systemMonitorGrid'>";
    section += "<!-- I dati verranno caricati dinamicamente -->";
    section += "</div>";
    section += "</div>";
    return section;
}

String MonitorUIRoutes::generateHeapMonitorSection()
{
    String section = "<div class='monitor-section section-divider'>";
    section += "<h2>💾 Memory Usage</h2>";
    section += viewGraph::initCirularProgressBarGraph();
    
    // Correggo il calcolo dell'heap per evitare NaN
    size_t heapFree = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t heapTotalOriginal = heap_caps_get_total_size(MALLOC_CAP_8BIT);
    
    // Validazione dei valori per evitare NaN
    if (heapTotalOriginal == 0 || heapFree > heapTotalOriginal) {
        // Se i valori non sono validi, uso valori di default
        heapTotalOriginal = 327680; // 320KB default per ESP32
        heapFree = heapTotalOriginal / 2; // 50% libero come default
    }
    
    // Calcolo corretto: prima calcolo used, poi applico il fattore di correzione se necessario
    size_t heapUsedOriginal = heapTotalOriginal - heapFree;
    
    // Applico il fattore di correzione solo per la visualizzazione, mantenendo la proporzione
    size_t heapTotal = heapTotalOriginal;
    size_t heapUsed = heapUsedOriginal;
    
    // Debug: aggiungo log per verificare i valori
    Serial.println("Heap Debug - Total: " + String(heapTotal) + ", Free: " + String(heapFree) + ", Used: " + String(heapUsed));
    
    section += viewGraph::generateCirularProgressBarGraph("HEAP", heapUsed, heapTotal, "monitorHeapData", 1000);
    section += viewGraph::endCirularProgressBarGraph();
    section += "</div>";
    return section;
}

String MonitorUIRoutes::generateStackUsageSection()
{
    String section = "<div class='monitor-section section-divider'>";
    section += "<h2>⚙️ Task Stack Usage</h2>";
    PinoutData *pinoutData = SystemState::getInstance()->pinoutData;
    section += viewGraph::initCirularProgressBarGraph();
    
    for (auto pin = pinoutData->begin(); pin != pinoutData->end(); ++pin)
    {
        if (pin->getRecordingTask() != NULL)
        {
            size_t stackUsed = pin->getUsedStackInWords() * 4;
            size_t stackTotal = pin->getStackSizeInWords() * 4;
            section += viewGraph::generateCirularProgressBarGraph("Pin" + String(pin->getNumber()) + "Stack", stackUsed, stackTotal, "/monitorPinStack?pin=" + String(pin->getNumber()), 1000);
        }
    }
    section += viewGraph::endCirularProgressBarGraph();
    section += "</div>";
    return section;
}

String MonitorUIRoutes::generateMonitorJavaScript()
{
    // ...existing code... (il JavaScript che gestisce l'aggiornamento delle card e le funzioni)
    String script = "<script>";
    script += "function updateSystemMonitor() {";
    script += "  fetch('/systemStats').then(response => response.json()).then(data => {";
    script += "    const grid = document.getElementById('systemMonitorGrid');";
    script += "    grid.innerHTML = '';";
    // Heap Memory Card
    script += "    grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "    grid.innerHTML += '<h3>💾 Heap Memory Details</h3>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Used / Total</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-value\">' + (data.heap.used/1024).toFixed(1) + ' KB / ' + (data.heap.total/1024).toFixed(1) + ' KB</div>';";
    script += "    const heapPercent = (data.heap.used / data.heap.total * 100);";
    script += "    grid.innerHTML += '<div class=\"progress-bar\"><div class=\"progress-fill\" style=\"width: ' + heapPercent + '%\"></div></div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Min Free: ' + (data.heap.minFree/1024).toFixed(1) + ' KB</div>';";
    script += "    const minFreePercent = (data.heap.minFree / data.heap.total * 100);";
    script += "    const statusClass = minFreePercent > 10 ? 'status-ok' : (minFreePercent > 5 ? 'status-warning' : 'status-critical');";
    script += "    grid.innerHTML += '<div class=\"monitor-label ' + statusClass + '\">Status: ' + (minFreePercent > 10 ? 'OK' : (minFreePercent > 5 ? 'Warning' : 'Critical')) + '</div>';";
    script += "    grid.innerHTML += '</div>';";
    // PSRAM Card
    script += "    if (data.psram.total > 0) {";
    script += "      grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "      grid.innerHTML += '<h3>🧠 PSRAM</h3>';";
    script += "      grid.innerHTML += '<div class=\"monitor-label\">Used / Total</div>';";
    script += "      grid.innerHTML += '<div class=\"monitor-value\">' + (data.psram.used/1024).toFixed(1) + ' KB / ' + (data.psram.total/1024).toFixed(1) + ' KB</div>';";
    script += "      const psramPercent = (data.psram.used / data.psram.total * 100);";
    script += "      grid.innerHTML += '<div class=\"progress-bar\"><div class=\"progress-fill\" style=\"width: ' + psramPercent + '%\"></div></div>';";
    script += "      grid.innerHTML += '</div>';";
    script += "    }";
    // FreeRTOS Card
    script += "    grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "    grid.innerHTML += '<h3>⚙️ FreeRTOS Tasks</h3>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Active Tasks</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-value\">' + data.freertos.taskCount + '</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Main Stack Free: ' + (data.freertos.mainStackFree/1024).toFixed(1) + ' KB</div>';";
    script += "    const stackPercent = (data.freertos.mainStackFree / 8192 * 100);";
    script += "    const stackStatus = stackPercent > 25 ? 'status-ok' : (stackPercent > 10 ? 'status-warning' : 'status-critical');";
    script += "    grid.innerHTML += '<div class=\"monitor-label ' + stackStatus + '\">Stack Status: ' + (stackPercent > 25 ? 'OK' : (stackPercent > 10 ? 'Warning' : 'Critical')) + '</div>';";
    script += "    grid.innerHTML += '</div>';";
    // System Info Card
    script += "    const uptimeHours = (data.system.uptime / 3600000).toFixed(1);";
    script += "    const uptimeDays = (data.system.uptime / 86400000).toFixed(1);";
    script += "    grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "    grid.innerHTML += '<h3>🖥️ System Info</h3>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Uptime</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-value\">' + uptimeHours + ' hours (' + uptimeDays + ' days)</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">CPU Freq: ' + data.system.cpuFreq + ' MHz</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Flash Free: ' + (data.system.freeSketchSpace/1024).toFixed(0) + ' KB</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Chip ID: ' + data.system.chipId + '</div>';";
    script += "    grid.innerHTML += '</div>';";
    // WiFi Card
    script += "    const wifiStatus = data.wifi.connected === 'true' ? 'Connected' : 'Disconnected';";
    script += "    const wifiClass = data.wifi.connected === 'true' ? 'status-ok' : 'status-critical';";
    script += "    grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "    grid.innerHTML += '<h3>📶 WiFi Status</h3>';";
    script += "    grid.innerHTML += '<div class=\"monitor-label\">Connection</div>';";
    script += "    grid.innerHTML += '<div class=\"monitor-value ' + wifiClass + '\">' + wifiStatus + '</div>';";
    script += "    if (data.wifi.connected === 'true') {";
    script += "      const rssiClass = data.wifi.rssi > -50 ? 'status-ok' : (data.wifi.rssi > -70 ? 'status-warning' : 'status-critical');";
    script += "      grid.innerHTML += '<div class=\"monitor-label\">RSSI: <span class=\"' + rssiClass + '\">' + data.wifi.rssi + ' dBm</span></div>';";
    script += "      grid.innerHTML += '<div class=\"monitor-label\">IP: ' + data.wifi.localIP + '</div>';";
    script += "    }";
    script += "    grid.innerHTML += '</div>';";
    script += "  }).catch(error => console.error('Error:', error));";
    script += "}";
    
    // Export function
    script += "function exportSystemData() {";
    script += "  fetch('/systemStats').then(response => response.json()).then(data => {";
    script += "    const timestamp = new Date().toISOString();";
    script += "    let csv = 'Timestamp,Parameter,Value,Unit\\n';";
    script += "    csv += timestamp + ',Heap Used,' + data.heap.used + ',bytes\\n';";
    script += "    csv += timestamp + ',Heap Total,' + data.heap.total + ',bytes\\n';";
    script += "    csv += timestamp + ',Heap Min Free,' + data.heap.minFree + ',bytes\\n';";
    script += "    csv += timestamp + ',PSRAM Used,' + data.psram.used + ',bytes\\n';";
    script += "    csv += timestamp + ',PSRAM Total,' + data.psram.total + ',bytes\\n';";
    script += "    csv += timestamp + ',Task Count,' + data.freertos.taskCount + ',count\\n';";
    script += "    csv += timestamp + ',Main Stack Free,' + data.freertos.mainStackFree + ',bytes\\n';";
    script += "    csv += timestamp + ',Uptime,' + data.system.uptime + ',ms\\n';";
    script += "    csv += timestamp + ',CPU Frequency,' + data.system.cpuFreq + ',MHz\\n';";
    script += "    csv += timestamp + ',Flash Free,' + data.system.freeSketchSpace + ',bytes\\n';";
    script += "    csv += timestamp + ',WiFi RSSI,' + data.wifi.rssi + ',dBm\\n';";
    script += "    const csvFile = new Blob([csv], { type: 'text/csv' });";
    script += "    const downloadLink = document.createElement('a');";
    script += "    downloadLink.download = 'system_monitor_' + new Date().getTime() + '.csv';";
    script += "    downloadLink.href = window.URL.createObjectURL(csvFile);";
    script += "    downloadLink.style.display = 'none';";
    script += "    document.body.appendChild(downloadLink);";
    script += "    downloadLink.click();";
    script += "    document.body.removeChild(downloadLink);";
    script += "  }).catch(error => console.error('Export error:', error));";
    script += "}";
    
    // Cleanup function
    script += "function cleanupHeap() {";
    script += "  fetch('/optimizeHeap').then(response => response.json()).then(data => {";
    script += "    if (data.success) {";
    script += "      alert('Heap cleanup eseguito con successo!');";
    script += "      updateSystemMonitor();";
    script += "    } else {";
    script += "      alert('Errore durante il cleanup del heap: ' + data.error);";
    script += "    }";
    script += "  }).catch(error => console.error('Cleanup error:', error));";
    script += "}";
    
    // Auto-refresh
    script += "document.addEventListener('DOMContentLoaded', function() {";
    script += "  updateSystemMonitor();";
    script += "  setInterval(updateSystemMonitor, 3000);";
    script += "});";
    script += "</script>";
    
    return script;
}