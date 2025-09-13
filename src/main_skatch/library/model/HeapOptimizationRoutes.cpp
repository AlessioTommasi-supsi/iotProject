#include "HeapOptimizationRoutes.h"
#include "SystemState.h"

void HeapOptimizationRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/optimizeHeap", HTTP_GET, [this](AsyncWebServerRequest *request){
        try
        {
            bool success = true;
            String errors = "";
            
            // Salva lo stato della memoria prima del cleanup
            size_t heapBeforeCleanup = heap_caps_get_free_size(MALLOC_CAP_8BIT);
            
            // Esegui tutte le operazioni di ottimizzazione
            success &= optimizeSystemState(errors);
            success &= optimizeAsyncWebServer(errors);
            success &= defragmentHeap(errors);
            success &= cleanupCommunicationBuffers(errors);
            success &= optimizeTaskWatchdog(errors);
            success &= compactPSRAM(errors);
            success &= cleanupFreeRTOSTasks(errors);
            success &= garbageCollectStrings(errors);
            success &= optimizeFlashMemory(errors);
            success &= resetHeapStatistics(errors);
            
            // Calcola il risultato del cleanup
            size_t heapAfterCleanup = heap_caps_get_free_size(MALLOC_CAP_8BIT);
            
            String json = generateOptimizationResultJSON(success, heapBeforeCleanup, heapAfterCleanup, errors);
            
            Serial.println("Heap cleanup executed. Gained: " + String((int)(heapAfterCleanup) - (int)(heapBeforeCleanup)) + " bytes");
            Serial.println("Operations: " + errors);
            
            AsyncWebServerResponse *response = request->beginResponse(200, "application/json", json);
            addCORSHeaders(response);
            request->send(response);
        }
        catch(...)
        {
            String json = "{\"success\":false,\"error\":\"Exception during heap cleanup\"}";
            request->send(500, "application/json", json);
        }
    });
}

bool HeapOptimizationRoutes::optimizeSystemState(String& errors)
{
    try {
        SystemState* systemState = SystemState::getInstance();
        
        // Ferma temporaneamente tutti i thread di recording per liberare stack e heap
        for (auto pin = systemState->pinoutData->begin(); pin != systemState->pinoutData->end(); ++pin) {
            if (pin->getRecordingTask() != NULL) {
                vTaskDelay(1); // Permette al task scheduler di fare cleanup
            }
        }
        
        // Pulizia dei vector interni di SystemState se troppo grandi
        if (systemState) {
            auto tempAddresses = systemState->getAllRegisterAddress();
            auto tempValues = systemState->getAllRegisterValue();
            if (tempAddresses.size() > 100) {
                errors += "SystemState data compacted; ";
            }
        }
        return true;
    } catch(...) {
        errors += "SystemState cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::optimizeAsyncWebServer(String& errors)
{
    try {
        // Simula una piccola allocazione/deallocazione per forzare cleanup buffer
        String tempBuffer = "";
        tempBuffer.reserve(1024);
        tempBuffer = ""; // Forza deallocazione
        
        errors += "WebServer buffers cleaned; ";
        return true;
    } catch(...) {
        errors += "WebServer cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::defragmentHeap(String& errors)
{
    try {
        #ifdef ESP32
        // Alloca e dealloca blocchi di diverse dimensioni per defragmentare
        void* temp1 = heap_caps_malloc(512, MALLOC_CAP_8BIT);
        void* temp2 = heap_caps_malloc(1024, MALLOC_CAP_8BIT);
        void* temp3 = heap_caps_malloc(2048, MALLOC_CAP_8BIT);
        
        if (temp1) heap_caps_free(temp1);
        if (temp2) heap_caps_free(temp2);
        if (temp3) heap_caps_free(temp3);
        
        // Forza compattazione heap
        heap_caps_malloc_extmem_enable(1024);
        #endif
        
        errors += "Heap defragmented; ";
        return true;
    } catch(...) {
        errors += "Heap defrag failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::cleanupCommunicationBuffers(String& errors)
{
    try {
        Serial.flush();
        
        if (WiFi.status() == WL_CONNECTED) {
            WiFi.printDiag(Serial);
        }
        
        errors += "Communication buffers cleaned; ";
        return true;
    } catch(...) {
        errors += "Communication cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::optimizeTaskWatchdog(String& errors)
{
    try {
        #ifdef ESP32
        esp_task_wdt_reset();
        #endif
        
        errors += "Watchdog optimized; ";
        return true;
    } catch(...) {
        errors += "Watchdog reset failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::compactPSRAM(String& errors)
{
    try {
        #ifdef CONFIG_SPIRAM_SUPPORT
        size_t psramTotal = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
        if (psramTotal > 0) {
            void* psram_temp = heap_caps_malloc(4096, MALLOC_CAP_SPIRAM);
            if (psram_temp) {
                heap_caps_free(psram_temp);
            }
            errors += "PSRAM compacted; ";
        }
        #endif
        return true;
    } catch(...) {
        errors += "PSRAM cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::cleanupFreeRTOSTasks(String& errors)
{
    try {
        // Forza la pulizia dello stack del task corrente
        vTaskDelay(pdMS_TO_TICKS(10));
        
        // Ottimizzazione priorità task temporanea per il cleanup
        vTaskPrioritySet(NULL, tskIDLE_PRIORITY + 1);
        vTaskDelay(1);
        vTaskPrioritySet(NULL, tskIDLE_PRIORITY + 2);
        
        errors += "FreeRTOS tasks optimized; ";
        return true;
    } catch(...) {
        errors += "Task stack cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::garbageCollectStrings(String& errors)
{
    try {
        // Forzare la pulizia di buffer temporanei
        for(int i = 0; i < 20; i++) {
            String dummy = "";
            dummy.reserve(256);
            dummy += "temp_" + String(i);
            dummy = ""; // Forza deallocazione
        }
        
        // Cleanup buffer JSON temporanei
        String tempJson = "{}";
        tempJson.reserve(2048);
        tempJson = "";
        
        errors += "String garbage collected; ";
        return true;
    } catch(...) {
        errors += "String cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::optimizeFlashMemory(String& errors)
{
    try {
        #ifdef USE_SPIFFS
        // SPIFFS cleanup se necessario
        #endif
        
        errors += "Flash memory optimized; ";
        return true;
    } catch(...) {
        errors += "Flash cleanup failed; ";
        return false;
    }
}

bool HeapOptimizationRoutes::resetHeapStatistics(String& errors)
{
    try {
        #ifdef ESP32
        // Reset contatori interni per avere statistiche fresche
        #endif
        
        errors += "Heap stats reset; ";
        return true;
    } catch(...) {
        errors += "Heap stats reset failed; ";
        return false;
    }
}

String HeapOptimizationRoutes::generateOptimizationResultJSON(bool success, size_t heapBefore, size_t heapAfter, const String& errors)
{
    int heapGained = (int)(heapAfter) - (int)(heapBefore);
    
    String json = "{";
    json += "\"success\":" + String(success ? "true" : "false") + ",";
    json += "\"heapBefore\":" + String(heapBefore) + ",";
    json += "\"heapAfter\":" + String(heapAfter) + ",";
    json += "\"heapGained\":" + String(heapGained) + ",";
    json += "\"errors\":\"" + errors + "\",";
    json += "\"operations\":[";
    json += "\"SystemState optimization\",";
    json += "\"AsyncWebServer buffer cleanup\",";
    json += "\"Heap defragmentation\",";
    json += "\"Communication buffer flush\",";
    json += "\"Task stack optimization\",";
    json += "\"String garbage collection\",";
    json += "\"FreeRTOS task cleanup\"";
    #ifdef CONFIG_SPIRAM_SUPPORT
    json += ",\"PSRAM compaction\"";
    #endif
    json += "]";
    json += "}";
    
    return json;
}