#include "modbusRoutes.h"


void ModbusRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/graph", HTTP_GET, [](AsyncWebServerRequest *request){
        String htmlContent = viewGraph::generateHTML();
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr); 
         
    });
    
    server.on("/history", HTTP_GET, [](AsyncWebServerRequest *request){
        try {
            String htmlContent = viewHistory::generateHTML();
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(200, "text/html", htmlContentPtr);
        } catch (const std::exception& e) {
            Serial.println("Error in /history route: " + String(e.what()));
            request->send(500, "text/html", "Error loading history page");
        } catch (...) {
            Serial.println("Unknown error in /history route");
            request->send(500, "text/html", "Unknown error occurred");
        }
    });

    // Nuova rotta per la cronologia separata di Modbus
    server.on("/modbus_history", HTTP_GET, [](AsyncWebServerRequest *request) {
        try {
            String htmlContent = viewModbusHistory::generateHTML();
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(200, "text/html", htmlContentPtr);
        } catch (const std::exception& e) {
            Serial.println("Error in /modbus_history route: " + String(e.what()));
            request->send(500, "text/html", "Error loading modbus history page");
        } catch (...) {
            Serial.println("Unknown error in /modbus_history route");
            request->send(500, "text/html", "Unknown error occurred");
        }
    });

    server.on("/getHistoryContent", HTTP_GET, [](AsyncWebServerRequest *request){
        String content = "";
        std::vector<float> valuesVector = SystemState::getInstance()->getAllRegisterValue();
        std::vector<int> addresses = SystemState::getInstance()->getAllRegisterAddress();

        // Loop through each value in the vector in reverse order
        for (size_t i = valuesVector.size(); i > 0; i--)
        {
            size_t index = i - 1;
            content += "<tr>";
            content += "<td>" + String(addresses[index]) + "</td>"; // Display the address

            // Display the value with an input field for editing inside a form
            content += "<td>";
            content += "<form action='/editRegister' method='GET'>";
            content += "<input type='hidden' name='index' value='" + String(index) + "'>";
            content += "<input type='text' class='edit-input' name='value' value='" + String(valuesVector[index]) + "'>";
            content += "<input type='submit' value='Edit' class='action-link edit-link'>";
            content += "</form>";
            content += "</td>";

            // Add delete button with link
            content += "<td>";
            content += "<a href='/deleteRegister?index=" + String(index) + "' class='action-link delete-link'>Delete</a>"; // Delete link
            content += "</td>";

            content += "</tr>";
        }

        request->send(200, "text/html", content);
    });

    // Nuovo endpoint per aggiornamento dinamico cronologia Modbus
    server.on("/getModbusValuesHistory", HTTP_GET, [](AsyncWebServerRequest *request) {
        try {
            String content = viewModbusHistory::modbusContent();
            request->send(200, "text/html", content);
        } catch (const std::exception& e) {
            Serial.println("Error in /getModbusValuesHistory route: " + String(e.what()));
            request->send(500, "text/html", "Error loading modbus history");
        } catch (...) {
            Serial.println("Unknown error in /getModbusValuesHistory route");
            request->send(500, "text/html", "Unknown error occurred");
        }
    });

    server.on("/deleteRegister", HTTP_GET, [](AsyncWebServerRequest *request){
        String registerAddress = request->getParam("index")->value();
        SystemState::getInstance()->deleteValue(registerAddress.toInt());
        String htmlContent = viewModbusHistory::generateHTML();
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr); 
             
    });

    server.on("/editRegister", HTTP_GET, [](AsyncWebServerRequest *request){
        String registerAddress = request->getParam("index")->value();
        String registerValue = request->getParam("value")->value();
        SystemState::getInstance()->editValue(registerAddress.toInt(), registerValue.toFloat());
        String htmlContent = viewModbusHistory::generateHTML();
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr); 
             
    });

    server.on("/currentregister", HTTP_GET, [](AsyncWebServerRequest *request){
            String popup = "";
            if (request->hasParam("popup")) {
                popup = request->getParam("popup")->value();
                popup.replace("%20", " ");
            }
            String htmlContent = viewCurrentRegister::generateHTML(popup);
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(200, "text/html", htmlContentPtr); 
             
    });


    server.on("/modbusMaster", HTTP_GET, [](AsyncWebServerRequest *request){
        try {
            String registerAddress = request->getParam("registerAddress")->value();
            String registerType = request->getParam("registerType")->value();

            Serial.println("Request for modbusMaster");
            Serial.println("Register Address: " + registerAddress);
            Serial.println("Register Type: " + registerType);

            float registerValue = 0.0;
            
            if (registerType == "int") {
                // Read integer register from Modbus Master
                registerValue = (float)SystemState::masterModbus->readHoldingIntRegisters(registerAddress.toInt());
            }
            else if (registerType == "float") {
                // Read float register from Modbus Master
                registerValue = SystemState::masterModbus->readHoldingFloatRegisters(registerAddress.toInt());
            }
            else {
                request->send(400, "text/plain", "Invalid register type");
                return;
            }

            // Generate HTML response with register monitoring interface and full CSS
            String htmlContent = viewCurrentRegister::generateOfflineHTML(registerAddress, registerValue, "");
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(200, "text/html", htmlContentPtr);
        }
        catch (const std::exception& e) {
            Serial.println("Error in modbusMaster: " + String(e.what()));
            String popupScript = "showPopup('Error reading register: " + String(e.what()) + "');";
            String htmlContent = viewCurrentRegister::generateMasterHtml("", 0.0, popupScript);
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(500, "text/html", htmlContentPtr);
        }
        catch (...) {
            Serial.println("Unknown error in modbusMaster");
            String popupScript = "showPopup('Unknown error occurred while reading register');";
            String htmlContent = viewCurrentRegister::generateMasterHtml("", 0.0, popupScript);
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(500, "text/html", htmlContentPtr);
        }
    });

    server.on("/modbusSlave", HTTP_GET, [](AsyncWebServerRequest *request){
        try {
            String registerAddress = request->getParam("registerAddress")->value();
            String registerValue   = request->getParam("registerValue")->value();
            String registerType    = request->getParam("registerType")->value();

            Serial.println("Request for modbusSlave");
            Serial.println("Register Address: " + registerAddress);
            Serial.println("Register Value: " + registerValue);
            Serial.println("Register Type: " + registerType);
        
            if (registerType == "int") {
                ModBusSlaveController::getInstance()->writeIntRegister(registerAddress.toInt(), registerValue.toInt());
            }
            else if (registerType == "float") {
                ModBusSlaveController::getInstance()->writeFloatRegister(registerAddress.toInt(), registerValue.toFloat());
            }
            else {
                request->send(400, "text/plain", "Invalid register type");
                return;
            }
        
            // Initialize or verify polling state
            ModBusSlaveController::getInstance()->poll();
        
            // Send a simple success page with OK button to return to /currentregister
            String htmlContent = viewCurrentRegister::generateHtmlSlave();
            request->send(200, "text/html", htmlContent.c_str());
        }
        catch (const std::exception& e) {
            Serial.println("Error in modbusSlave: " + String(e.what()));
            String popupScript = "showPopup('Error writing register: " + String(e.what()) + "');";
            String htmlContent = viewCurrentRegister::generateHTML(popupScript);
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(500, "text/html", htmlContentPtr);
        }
        catch (...) {
            Serial.println("Unknown error in modbusSlave");
            String popupScript = "showPopup('Unknown error occurred while writing register');";
            String htmlContent = viewCurrentRegister::generateHTML(popupScript);
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(500, "text/html", htmlContentPtr);
        }
    });
    
    


    server.on("/modbusMasterPageContent", HTTP_GET, [](AsyncWebServerRequest *request){
        try
        {
            String content = "";
            Serial.println("request of modbusMasterPageContent");
            
            String registerAddress = request->getParam("registerAddress")->value();
            float registerValue = request->getParam("registerValue")->value().toFloat();
            Serial.println("valoriPassati: ");
            Serial.print("registerAddress: " + registerAddress);
            Serial.println("  registerValue: " + String(registerValue));
            
            // Usa solo il contenuto della pagina senza dipendenze esterne
            content += viewCurrentRegister::pageContent(registerAddress, registerValue);
            Serial.println("generato il contenuto della pagina");

            AsyncWebServerResponse *response = request->beginResponse(200, "text/html", content);
            response->addHeader("Access-Control-Allow-Origin", "*");
            response->addHeader("Cache-Control", "no-cache"); // Evita problemi di cache
            request->send(response);
            
        }
        catch(...)
        {
            Serial.println("Error during get modbusMasterPageContent");
            request->send(200, "text/html", "Error: An error occurred");
        }          
    });

    server.on("/storevalue", HTTP_GET, [](AsyncWebServerRequest *request){
            String registerValue = request->getParam("registerValue")->value();
            String registerAddress = request->getParam("registerAddress")->value();

            SystemState::getInstance()->pushRegister(registerAddress.toInt(), registerValue.toFloat());

            String htmlContent = viewCurrentRegister::generateHTMLConfirm(registerAddress, registerValue.toFloat());
            const char *htmlContentPtr = htmlContent.c_str();
            request->send(200, "text/html", htmlContentPtr); 
             
    });

    server.on("/startRecording", HTTP_GET, [](AsyncWebServerRequest *request){
    try {
        String milliseconds = request->getParam("milliseconds")->value();
        String registerAddress = request->getParam("registerAddress")->value();

        Serial.println("Start recording register " + registerAddress + " every " + milliseconds + " milliseconds");
        //Serial.println("integer milliseconds: " + milliseconds.toInt());
        
        SystemState::getInstance()->startRecordingRegister(registerAddress.toInt(), milliseconds.toInt());

        String popupScript = "showPopup('Recording started');";
        String htmlContent = viewCurrentRegister::generateMasterHtml(registerAddress, 0.0, popupScript);
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr);
         
    } catch (const std::exception &e) {
        String errorMessage = "Error: ";
        errorMessage += e.what();
        String popupScript = "showPopup('" + errorMessage + "');";
        String htmlContent = viewCurrentRegister::generateMasterHtml("", 0.0, popupScript);
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(500, "text/html", htmlContentPtr);
    } catch (...) {
        String popupScript = "showPopup('Unknown error occurred');";
        String htmlContent = viewCurrentRegister::generateMasterHtml("", 0.0, popupScript);
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(500, "text/html", htmlContentPtr);
    }
    });

    server.on("/stopRecording", HTTP_GET, [](AsyncWebServerRequest *request){
    try {
        String registerAddress = request->getParam("registerAddress")->value();
        SystemState::getInstance()->stopRecordingRegister(registerAddress.toInt());

        String popupScript = "showPopup('Recording stopped');";
        String htmlContent = viewCurrentRegister::generateMasterHtml(registerAddress, 0.0, popupScript);
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr);
         
    } catch (const std::exception &e) {
        String errorMessage = "Error: ";
        errorMessage += e.what();
        String popupScript = "showPopup('" + errorMessage + "');";
        String htmlContent = viewCurrentRegister::generateMasterHtml("", 0.0, popupScript);
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(500, "text/html", htmlContentPtr);
    } catch (...) {
        String popupScript = "showPopup('Unknown error occurred');";
        String htmlContent = viewCurrentRegister::generateMasterHtml("", 0.0, popupScript);
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(500, "text/html", htmlContentPtr);
    }
    });


    // update del grafico!
    server.on("/getRegisterValues", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("address")) {
        String address = request->getParam("address")->value();
        std::vector<float> values = SystemState::getInstance()->getAllRegisterValue(address.toInt());

        String json = "[";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) json += ",";
            json += String(values[i]);
        }
        json += "]";

        request->send(200, "application/json", json);
         
    } else {
        request->send(400, "application/json", "{\"error\":\"Address parameter missing\"}");
    } 
    });

    server.on("/currentRegisterPageContent", HTTP_GET, [](AsyncWebServerRequest *request){
        try {
            String content = "";
            String registerAddress = request->hasParam("registerAddress") ? request->getParam("registerAddress")->value() : "";
            float registerValue = request->hasParam("registerValue") ? request->getParam("registerValue")->value().toFloat() : 0.0;
            
            content = viewCurrentRegister::pageContent(registerAddress, registerValue);
            
            AsyncWebServerResponse *response = request->beginResponse(200, "text/html", content);
            response->addHeader("Access-Control-Allow-Origin", "*");
            response->addHeader("Cache-Control", "no-cache");
            request->send(response);
        } catch (...) {
            request->send(500, "text/html", "Error loading register content");
        }
    });

}