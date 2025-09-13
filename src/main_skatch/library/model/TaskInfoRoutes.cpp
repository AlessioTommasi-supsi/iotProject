#include "TaskInfoRoutes.h"
#include "SystemState.h"
#include "PinoutData.h"

void TaskInfoRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/taskInfo", HTTP_GET, [this](AsyncWebServerRequest *request){
        try
        {
            String response = generateTaskInfoPage();
            request->send(200, "text/html", response);
        }
        catch(...)
        {
            String response = "Error getting task information";
            request->send(500, "text/html", response);
        }
    });
}

String TaskInfoRoutes::generateTaskInfoPage()
{
    String response = "<!DOCTYPE html><html><head><title>Task Info</title>";
    response += "<style>body{font-family:Arial,sans-serif;margin:20px;} .info-section{margin:20px 0;padding:15px;background:#f5f5f5;border-radius:8px;}</style>";
    response += "</head><body>";
    response += "<h1>FreeRTOS Task Information</h1>";
    
    response += generateTaskStatisticsSection();
    response += generateSystemMemorySection();
    response += generatePinTaskSection();
    response += generateCPUInfoSection();
    
    response += "<div style='margin-top:20px;'>";
    response += "<a href='/monitor' style='padding:10px 20px;background:#007cba;color:white;text-decoration:none;border-radius:5px;'>← Back to Monitor</a>";
    response += "</div>";
    response += "</body></html>";
    
    return response;
}

String TaskInfoRoutes::generateTaskStatisticsSection()
{
    String section = "<div class='info-section'>";
    section += "<h2>Task Statistics</h2>";
    section += "<p><strong>Total Tasks:</strong> " + String(uxTaskGetNumberOfTasks()) + "</p>";
    section += "<p><strong>Main Task Stack Free:</strong> " + String(uxTaskGetStackHighWaterMark(NULL) * 4) + " bytes</p>";
    section += "<p><strong>Scheduler State:</strong> " + String(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING ? "Running" : "Not Running") + "</p>";
    section += "</div>";
    return section;
}

String TaskInfoRoutes::generateSystemMemorySection()
{
    String section = "<div class='info-section'>";
    section += "<h2>System Memory Info</h2>";
    section += "<p><strong>Heap Free:</strong> " + String(heap_caps_get_free_size(MALLOC_CAP_8BIT)) + " bytes</p>";
    section += "<p><strong>Heap Min Free:</strong> " + String(heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT)) + " bytes</p>";
    section += "<p><strong>Heap Total:</strong> " + String(heap_caps_get_total_size(MALLOC_CAP_8BIT)) + " bytes</p>";
    
    size_t psramTotal = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    if (psramTotal > 0) {
        section += "<p><strong>PSRAM Total:</strong> " + String(psramTotal) + " bytes</p>";
        section += "<p><strong>PSRAM Free:</strong> " + String(heap_caps_get_free_size(MALLOC_CAP_SPIRAM)) + " bytes</p>";
    }
    section += "</div>";
    return section;
}

String TaskInfoRoutes::generatePinTaskSection()
{
    String section = "<div class='info-section'>";
    section += "<h2>Pin Task Information</h2>";
    PinoutData *pinoutData = SystemState::getInstance()->pinoutData;
    bool hasActiveTasks = false;
    
    for (auto pin = pinoutData->begin(); pin != pinoutData->end(); ++pin) {
        if (pin->getRecordingTask() != NULL) {
            hasActiveTasks = true;
            section += "<p><strong>Pin " + String(pin->getNumber()) + " Task:</strong></p>";
            section += "<ul>";
            section += "<li>Stack Size: " + String(pin->getStackSizeInWords() * 4) + " bytes</li>";
            section += "<li>Stack Used: " + String(pin->getUsedStackInWords() * 4) + " bytes</li>";
            section += "<li>Stack Free: " + String((pin->getStackSizeInWords() - pin->getUsedStackInWords()) * 4) + " bytes</li>";
            float stackUsage = (float)pin->getUsedStackInWords() / pin->getStackSizeInWords() * 100;
            section += "<li>Stack Usage: " + String(stackUsage, 1) + "%</li>";
            section += "</ul>";
        }
    }
    
    if (!hasActiveTasks) {
        section += "<p>No active pin recording tasks</p>";
    }
    section += "</div>";
    return section;
}

String TaskInfoRoutes::generateCPUInfoSection()
{
    String section = "<div class='info-section'>";
    section += "<h2>CPU Information</h2>";
    section += "<p><strong>CPU Frequency:</strong> " + String(ESP.getCpuFreqMHz()) + " MHz</p>";
    section += "<p><strong>Chip Model:</strong> " + String(ESP.getChipModel()) + "</p>";
    section += "<p><strong>Chip Revision:</strong> " + String(ESP.getChipRevision()) + "</p>";
    section += "<p><strong>Flash Size:</strong> " + String(ESP.getFlashChipSize()) + " bytes</p>";
    section += "<p><strong>Free Sketch Space:</strong> " + String(ESP.getFreeSketchSpace()) + " bytes</p>";
    section += "</div>";
    return section;
}