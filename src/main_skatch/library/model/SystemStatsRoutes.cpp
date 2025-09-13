#include "SystemStatsRoutes.h"
#include "SystemState.h"

void SystemStatsRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/systemStats", HTTP_GET, [this](AsyncWebServerRequest *request){
        try
        {
            String json = generateSystemStatsJSON();
            AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
            addCORSHeaders(response);
            request->send(response);
        }
        catch(...)
        {
            String json = "{\"error\":\"An error occurred\"}";
            request->send(500, "application/json", json);
        }
    });

    server.on("/monitorHeapData", HTTP_GET, [this](AsyncWebServerRequest *request){
        try
        {
            String json = generateHeapStatsJSON();
            AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
            addCORSHeaders(response);
            request->send(response);
        }
        catch(...)
        {
            String json = "{\"error\":\"An error occurred\"}";
            request->send(500, "application/json", json);
        }
    });
}

String SystemStatsRoutes::generateSystemStatsJSON()
{
    String json = "{";
    json += generateHeapStatsJSON().substring(1, generateHeapStatsJSON().length() - 1) + ",";
    json += generatePSRAMStatsJSON().substring(1, generatePSRAMStatsJSON().length() - 1) + ",";
    json += generateFreeRTOSStatsJSON().substring(1, generateFreeRTOSStatsJSON().length() - 1) + ",";
    json += generateSystemInfoJSON().substring(1, generateSystemInfoJSON().length() - 1) + ",";
    json += generateWiFiStatsJSON().substring(1, generateWiFiStatsJSON().length() - 1);
    json += "}";
    return json;
}

String SystemStatsRoutes::generateHeapStatsJSON()
{
    size_t heapFree = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t heapTotalOriginal = heap_caps_get_total_size(MALLOC_CAP_8BIT);
    
    // Validazione dei valori per evitare NaN - stessa logica della UI
    if (heapTotalOriginal == 0 || heapFree > heapTotalOriginal) {
        // Se i valori non sono validi, uso valori di default
        heapTotalOriginal = 327680; // 320KB default per ESP32
        heapFree = heapTotalOriginal / 2; // 50% libero come default
    }
    
    size_t heapUsed = heapTotalOriginal - heapFree;
    size_t heapMinFree = heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT);
    
    // Validazione anche per heapMinFree
    if (heapMinFree > heapTotalOriginal) {
        heapMinFree = heapFree; // Non può essere maggiore del totale
    }
    
    String json = "{\"heap\":{";
    json += "\"used\":" + String(heapUsed) + ",";
    json += "\"total\":" + String(heapTotalOriginal) + ",";
    json += "\"free\":" + String(heapFree) + ",";
    json += "\"minFree\":" + String(heapMinFree);
    json += "}}";
    return json;
}

String SystemStatsRoutes::generatePSRAMStatsJSON()
{
    size_t psramFree = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    size_t psramTotal = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    size_t psramUsed = psramTotal - psramFree;
    
    String json = "{\"psram\":{";
    json += "\"used\":" + String(psramUsed) + ",";
    json += "\"total\":" + String(psramTotal) + ",";
    json += "\"free\":" + String(psramFree);
    json += "}}";
    return json;
}

String SystemStatsRoutes::generateFreeRTOSStatsJSON()
{
    UBaseType_t taskCount = uxTaskGetNumberOfTasks();
    size_t freeStackMain = uxTaskGetStackHighWaterMark(NULL);
    
    String json = "{\"freertos\":{";
    json += "\"taskCount\":" + String(taskCount) + ",";
    json += "\"mainStackFree\":" + String(freeStackMain * 4);
    json += "}}";
    return json;
}

String SystemStatsRoutes::generateSystemInfoJSON()
{
    unsigned long uptime = millis();
    uint32_t chipId = ESP.getEfuseMac() >> 24;
    uint32_t freeSketchSpace = ESP.getFreeSketchSpace();
    uint32_t sketchSize = ESP.getSketchSize();
    
    String json = "{\"system\":{";
    json += "\"uptime\":" + String(uptime) + ",";
    json += "\"chipId\":" + String(chipId) + ",";
    json += "\"sketchSize\":" + String(sketchSize) + ",";
    json += "\"freeSketchSpace\":" + String(freeSketchSpace) + ",";
    json += "\"cpuFreq\":" + String(ESP.getCpuFreqMHz());
    json += "}}";
    return json;
}

String SystemStatsRoutes::generateWiFiStatsJSON()
{
    String json = "{\"wifi\":{";
    json += "\"connected\":" + String(WiFi.status() == WL_CONNECTED ? "true" : "false") + ",";
    json += "\"rssi\":" + String(WiFi.RSSI()) + ",";
    json += "\"localIP\":\"" + WiFi.localIP().toString() + "\"";
    json += "}}";
    return json;
}