#include "SystemMonitorRoutes.h"
#include "viewGeneric.h"

void SystemMonitorRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/systemMonitor", HTTP_GET, [this](AsyncWebServerRequest *request){
        try
        {
            String html = generateAdvancedMonitorPage();
            request->send(200, "text/html", html);
        }
        catch(...)
        {
            String response = "Error loading system monitor";
            request->send(500, "text/html", response);
        }
    });
}

String SystemMonitorRoutes::generateAdvancedMonitorPage()
{
    String html = viewGeneric::basicHeader("System Monitor");
    html += viewGeneric::addExportCSVScript();
    
    html += "<h1>🔍 System Monitor</h1>";
    html += generateCommonMonitorCSS();
    
    // Aggiungi bottone export
    html += "<div style='text-align: center; margin: 20px 0;'>";
    html += "<button onclick=\"exportSystemData()\" style='background-color: #2196F3; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer;'>📊 Export System Data CSV</button>";
    html += "</div>";
    
    html += "<div class='monitor-grid' id='systemMonitorGrid'>";
    html += "<!-- I dati verranno caricati dinamicamente -->";
    html += "</div>";
    
    html += generateAdvancedMonitorScript();
    html += viewGeneric::defaultFooter();
    
    return html;
}

String SystemMonitorRoutes::generateAdvancedMonitorScript()
{
    String script = "<script>";
    script += "function updateSystemMonitor() {";
    script += "  fetch('/systemStats')";
    script += "    .then(response => response.json())";
    script += "    .then(data => {";
    script += "      const grid = document.getElementById('systemMonitorGrid');";
    script += "      grid.innerHTML = '';";
    
    // Card Heap Memory
    script += "      grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "        grid.innerHTML += '<h3>💾 Heap Memory</h3>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Used / Total</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-value\">' + (data.heap.used/1024).toFixed(1) + ' KB / ' + (data.heap.total/1024).toFixed(1) + ' KB</div>';";
    script += "        const heapPercent = (data.heap.used / data.heap.total * 100);";
    script += "        grid.innerHTML += '<div class=\"progress-bar\"><div class=\"progress-fill\" style=\"width: ' + heapPercent + '%\"></div></div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Min Free: ' + (data.heap.minFree/1024).toFixed(1) + ' KB</div>';";
    script += "      grid.innerHTML += '</div>';";
    
    // Card PSRAM
    script += "      if (data.psram.total > 0) {";
    script += "        grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "          grid.innerHTML += '<h3>🧠 PSRAM</h3>';";
    script += "          grid.innerHTML += '<div class=\"monitor-label\">Used / Total</div>';";
    script += "          grid.innerHTML += '<div class=\"monitor-value\">' + (data.psram.used/1024).toFixed(1) + ' KB / ' + (data.psram.total/1024).toFixed(1) + ' KB</div>';";
    script += "          const psramPercent = (data.psram.used / data.psram.total * 100);";
    script += "          grid.innerHTML += '<div class=\"progress-bar\"><div class=\"progress-fill\" style=\"width: ' + psramPercent + '%\"></div></div>';";
    script += "        grid.innerHTML += '</div>';";
    script += "      }";
    
    // Card FreeRTOS
    script += "      grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "        grid.innerHTML += '<h3>⚙️ FreeRTOS</h3>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Active Tasks</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-value\">' + data.freertos.taskCount + '</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Main Stack Free: ' + (data.freertos.mainStackFree/1024).toFixed(1) + ' KB</div>';";
    script += "      grid.innerHTML += '</div>';";
    
    // Card System Info
    script += "      const uptimeHours = (data.system.uptime / 3600000).toFixed(1);";
    script += "      const uptimeDays = (data.system.uptime / 86400000).toFixed(1);";
    script += "      grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "        grid.innerHTML += '<h3>🖥️ System</h3>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Uptime</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-value\">' + uptimeHours + ' hours (' + uptimeDays + ' days)</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">CPU Freq: ' + data.system.cpuFreq + ' MHz</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Flash Free: ' + (data.system.freeSketchSpace/1024).toFixed(0) + ' KB</div>';";
    script += "      grid.innerHTML += '</div>';";
    
    // Card WiFi
    script += "      const wifiStatus = data.wifi.connected === 'true' ? 'Connected' : 'Disconnected';";
    script += "      const wifiClass = data.wifi.connected === 'true' ? 'status-ok' : 'status-critical';";
    script += "      grid.innerHTML += '<div class=\"monitor-card\">';";
    script += "        grid.innerHTML += '<h3>📶 WiFi</h3>';";
    script += "        grid.innerHTML += '<div class=\"monitor-label\">Status</div>';";
    script += "        grid.innerHTML += '<div class=\"monitor-value ' + wifiClass + '\">' + wifiStatus + '</div>';";
    script += "        if (data.wifi.connected === 'true') {";
    script += "          grid.innerHTML += '<div class=\"monitor-label\">RSSI: ' + data.wifi.rssi + ' dBm</div>';";
    script += "          grid.innerHTML += '<div class=\"monitor-label\">IP: ' + data.wifi.localIP + '</div>';";
    script += "        }";
    script += "      grid.innerHTML += '</div>';";
    
    script += "    })";
    script += "    .catch(error => console.error('Error:', error));";
    script += "}";
    
    // Export function
    script += "function exportSystemData() {";
    script += "  fetch('/systemStats')";
    script += "    .then(response => response.json())";
    script += "    .then(data => {";
    script += "      const timestamp = new Date().toISOString();";
    script += "      let csv = 'Timestamp,Parameter,Value,Unit\\n';";
    script += "      csv += timestamp + ',Heap Used,' + data.heap.used + ',bytes\\n';";
    script += "      csv += timestamp + ',Heap Total,' + data.heap.total + ',bytes\\n';";
    script += "      csv += timestamp + ',Heap Min Free,' + data.heap.minFree + ',bytes\\n';";
    script += "      csv += timestamp + ',PSRAM Used,' + data.psram.used + ',bytes\\n';";
    script += "      csv += timestamp + ',PSRAM Total,' + data.psram.total + ',bytes\\n';";
    script += "      csv += timestamp + ',Task Count,' + data.freertos.taskCount + ',count\\n';";
    script += "      csv += timestamp + ',Main Stack Free,' + data.freertos.mainStackFree + ',bytes\\n';";
    script += "      csv += timestamp + ',Uptime,' + data.system.uptime + ',ms\\n';";
    script += "      csv += timestamp + ',CPU Frequency,' + data.system.cpuFreq + ',MHz\\n';";
    script += "      csv += timestamp + ',Flash Free,' + data.system.freeSketchSpace + ',bytes\\n';";
    script += "      csv += timestamp + ',WiFi RSSI,' + data.wifi.rssi + ',dBm\\n';";
    script += "      const csvFile = new Blob([csv], { type: 'text/csv' });";
    script += "      const downloadLink = document.createElement('a');";
    script += "      downloadLink.download = 'system_monitor_' + new Date().getTime() + '.csv';";
    script += "      downloadLink.href = window.URL.createObjectURL(csvFile);";
    script += "      downloadLink.style.display = 'none';";
    script += "      document.body.appendChild(downloadLink);";
    script += "      downloadLink.click();";
    script += "      document.body.removeChild(downloadLink);";
    script += "    });";
    script += "}";
    
    // Auto-refresh
    script += "document.addEventListener('DOMContentLoaded', function() {";
    script += "  updateSystemMonitor();";
    script += "  setInterval(updateSystemMonitor, 3000);";
    script += "});";
    script += "</script>";
    
    return script;
}