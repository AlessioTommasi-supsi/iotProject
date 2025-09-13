#include "MultiplexRoutes.h"
#include <vector>
#include <set>
#include "viewADS.h"
#include "viewADSHistory.h"

void MultiplexRoutes::defineRoutes(AsyncWebServer &server) {

    server.on("/multiplex_config", HTTP_GET, [](AsyncWebServerRequest *request) {
        String htmlContent = viewMultiplex::Config();
        request->send(200, "text/html", htmlContent);
    });
   
     server.on("/getADSValues", HTTP_GET, [](AsyncWebServerRequest *request) {
        ADS1115_controller* adsCtrl = ADS1115_controller::getInstance();
        
        if (adsCtrl->isInitializationFailed()) {
            // Se l'inizializzazione è fallita, restituisce un messaggio d'errore
            request->send(500, "text/html", "<h1>Error: ADS1115 Initialization Failed.</h1>");
            return;
        }
        
        const std::vector<float>& values = adsCtrl->getRecordedValues();
        String json = "[";
        for (size_t i = 0; i < values.size(); i++) {
            if (i > 0)
                json += ",";
            json += String(values[i]);
        }
        json += "]";
        request->send(200, "application/json", json);
    });

    // New endpoint for real-time value
    server.on("/getMultiplexValue", HTTP_GET, [](AsyncWebServerRequest *request) {
        ADS1115_controller* adsCtrl = ADS1115_controller::getInstance();
        
        String signalType = "";
        if (request->hasParam("signalType")) {
            signalType = request->getParam("signalType")->value();
        }
        
        // TEST MODE - simulate random values
        if (signalType == "TEST") {
            float simulatedValue = random(100, 500) / 10.0; // Random value between 10.0 and 50.0
            String json = "{\"value\":" + String(simulatedValue, 2) + ",\"signalType\":\"TEST\",\"mode\":\"simulation\"}";
            request->send(200, "application/json", json);
            return;
        }
        
        // Check if ADS is initialized for real signals
        if (adsCtrl->isInitializationFailed()) {
            String errorJson = "{\"error\":\"ADS1115 not initialized\",\"value\":0}";
            request->send(500, "application/json", errorJson);
            return;
        }
        
        adsCtrl->setChannel(signalType);
        
        // Try to read current value safely
        float currentValue = 0.0;
        try {
            currentValue = adsCtrl->read();
        } catch (...) {
            Serial.println("Error reading ADS1115 value");
            String errorJson = "{\"error\":\"Failed to read ADS1115\",\"value\":0}";
            request->send(500, "application/json", errorJson);
            return;
        }
        
        String json = "{\"value\":" + String(currentValue, 4) + ",\"signalType\":\"" + signalType + "\"}";
        request->send(200, "application/json", json);
    });

    // Endpoint to retry ADS initialization
    server.on("/reinitialize_ads", HTTP_GET, [](AsyncWebServerRequest *request) {
        ADS1115_controller* adsCtrl = ADS1115_controller::getInstance();
        adsCtrl->reinitialize();
        
        if (adsCtrl->isInitializationFailed()) {
            String htmlContent = "<h1>Reinitializzazione Fallita</h1>";
            htmlContent += "<p>L'ADS1115 non riesce ancora a inizializzarsi. Controlla i collegamenti I2C.</p>";
            htmlContent += "<form action='/reinitialize_ads' method='get'><button type='submit'>Riprova</button></form>";
            htmlContent += "<br><a href='/multiplex_config'>Torna alla configurazione</a>";
            request->send(500, "text/html", htmlContent);
        } else {
            String htmlContent = "<h1>Reinizializzazione Riuscita!</h1>";
            htmlContent += "<p>L'ADS1115 è stato inizializzato correttamente.</p>";
            htmlContent += "<br><a href='/multiplex_config'>Torna alla configurazione</a>";
            request->send(200, "text/html", htmlContent);
        }
    });

    server.on("/ads", HTTP_GET, [](AsyncWebServerRequest *request) {
        String content = viewADS::generateHTML();
        request->send(200, "text/html", content);
    });

    // Endpoint for TEST mode - simulated graph data
    server.on("/getTestValues", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Generate simulated data for the graph
        String json = "[";
        int numPoints = 20; // Generate 20 data points
        
        for (int i = 0; i < numPoints; i++) {
            if (i > 0) json += ",";
            
            // Create realistic looking data with some variation
            float baseValue = 25.0; // Base temperature value
            float variation = sin(i * 0.3) * 5.0; // Sine wave variation
            float noise = (random(-100, 100) / 100.0); // Small random noise
            float simulatedValue = baseValue + variation + noise;
            
            json += String(simulatedValue, 2);
        }
        
        json += "]";
        request->send(200, "application/json", json);
    });

    // Versione ottimizzata per bassa memoria di multiplex_graph con grafico leggero
    server.on("/multiplex_graph", HTTP_GET, [](AsyncWebServerRequest *request) {
        String signalType;
        String action = "";
        String milliseconds;

        if (request->hasParam("signalType")) {
            signalType = request->getParam("signalType")->value();
        } else {
            request->send(400, "text/plain", "Error: Missing signalType");
            return;
        }
        
        if (request->hasParam("action")) {
            action = request->getParam("action")->value();
        }
        
        if (request->hasParam("milliseconds")) {
            milliseconds = request->getParam("milliseconds")->value();
        } else {
            milliseconds = "1000";
        }

        // TEST MODE - modalità semplificata con grafico leggero
        if (signalType == "TEST") {
            if (action == "start_recording") {
                ADS1115_controller::getInstance()->startRecording(signalType, milliseconds.toInt());
                request->send(200, "text/plain", "Recording started");
                return;
            }
            if (action == "stop_recording") {
                ADS1115_controller::getInstance()->stopRecording();
                request->send(200, "text/plain", "Recording stopped");
                return;
            }
            
            // Pagina TEST con grafico leggero
            String html = "<!DOCTYPE html><html><head>";
            html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'>";
            html += "<title>TEST Mode</title>";
            html += "<style>";
            html += "body{font-family:Arial;margin:10px;text-align:center;background:#f5f5f5;}";
            html += ".container{max-width:900px;margin:0 auto;background:white;padding:20px;border-radius:10px;box-shadow:0 2px 10px rgba(0,0,0,0.1);}";
            html += ".value{font-size:24px;margin:15px 0;padding:20px;background:linear-gradient(45deg,#ff6b6b,#feca57);color:white;border-radius:10px;}";
            html += ".btn{padding:10px 20px;margin:8px;background:#4CAF50;color:white;border:none;border-radius:5px;cursor:pointer;font-size:14px;}";
            html += ".btn:hover{background:#45a049;}.btn.stop{background:#f44336;}.btn.stop:hover{background:#da190b;}";
            html += ".graph{width:100%;height:300px;border:2px solid #ddd;border-radius:8px;margin:20px 0;background:white;}";
            html += ".controls{margin:15px 0;padding:15px;background:#f9f9f9;border-radius:8px;}";
            html += ".status{margin:10px;padding:8px;border-radius:5px;font-weight:bold;}";
            html += ".recording{background:#d4edda;color:#155724;}.stopped{background:#f8d7da;color:#721c24;}";
            html += "</style></head><body>";
            html += "<div class='container'>";
            html += "<h1>🧪 TEST Mode</h1>";
            html += "<div class='value' id='currentValue'> </div>";
            
            html += "<canvas class='graph' id='chart' width='800' height='300'></canvas>";
            
            html += "<div class='controls'>";
            html += "<button class='btn' onclick='startRec()'>▶️ Start Recording</button>";
            html += "<button class='btn stop' onclick='stopRec()'>⏹️ Stop Recording</button>";
            html += "<div id='status' class='status stopped'>Recording Stopped</div>";
            html += "</div>";
            
            html += "<a href='/multiplex_config' style='padding:10px 20px;background:#FF9800;color:white;text-decoration:none;border-radius:5px;'>← Back</a>";
            html += "</div>";
            
            // JavaScript per grafico leggero
            html += "<script>";
            html += "let data=[],isRec=false;";
            html += "const canvas=document.getElementById('chart'),ctx=canvas.getContext('2d');";
            html += "function drawGraph(){";
            html += "ctx.clearRect(0,0,canvas.width,canvas.height);";
            html += "if(data.length<2)return;";
            html += "const maxVal=Math.max(...data),minVal=Math.min(...data),range=maxVal-minVal||1;";
            html += "const stepX=canvas.width/(data.length-1);";
            html += "ctx.strokeStyle='#4CAF50';ctx.lineWidth=2;ctx.beginPath();";
            html += "data.forEach((val,i)=>{";
            html += "const x=i*stepX,y=canvas.height-((val-minVal)/range)*canvas.height*0.8-canvas.height*0.1;";
            html += "i===0?ctx.moveTo(x,y):ctx.lineTo(x,y);});";
            html += "ctx.stroke();";
            html += "ctx.fillStyle='#666';ctx.font='12px Arial';";
            html += "ctx.fillText('Min: '+minVal.toFixed(1),10,canvas.height-10);";
            html += "ctx.fillText('Max: '+maxVal.toFixed(1),10,20);}";
            html += "function updateValue(){";
            html += "fetch('/getMultiplexValue?signalType=TEST').then(r=>r.json()).then(d=>{";
            html += "document.getElementById('currentValue').innerHTML='<strong>'+d.value.toFixed(2)+' 🧪</strong>';";
            html += "if(isRec){data.push(d.value);if(data.length>50)data.shift();drawGraph();}";
            html += "}).catch(e=>console.log('Error:',e));}";
            html += "function startRec(){fetch('/multiplex_graph?signalType=TEST&action=start_recording&milliseconds=1000').then(()=>{";
            html += "isRec=true;data=[];document.getElementById('status').className='status recording';";
            html += "document.getElementById('status').textContent='Recording Active ✅';});}";
            html += "function stopRec(){fetch('/multiplex_graph?signalType=TEST&action=stop_recording').then(()=>{";
            html += "isRec=false;document.getElementById('status').className='status stopped';";
            html += "document.getElementById('status').textContent='Recording Stopped ⏹️';});}";
            html += "setInterval(updateValue,2000);updateValue();drawGraph();";
            html += "</script></body></html>";
            
            request->send(200, "text/html", html);
            return;
        }

        // Per segnali reali, controlla ADS
        ADS1115_controller* adsCtrl = ADS1115_controller::getInstance();
        
        if (adsCtrl->isInitializationFailed()) {
            String html = "<!DOCTYPE html><html><head><title>ADS Error</title></head><body style='text-align:center;margin:50px;'>";
            html += "<h1>❌ ADS1115 Error</h1>";
            html += "<p>L'ADS1115 non è inizializzato correttamente.</p>";
            html += "<a href='/reinitialize_ads' style='padding:10px 20px;background:#f44336;color:white;text-decoration:none;border-radius:5px;'>Reinitializza ADS</a><br><br>";
            html += "<a href='/multiplex_config'>← Torna alla configurazione</a>";
            html += "</body></html>";
            request->send(500, "text/html", html);
            return;
        }

        // Gestisci azioni per segnali reali
        if (request->hasParam("milliseconds")) {
            adsCtrl->recordingInterval = milliseconds.toInt();
        }
        
        if (action == "start_recording") {
            adsCtrl->startRecording(signalType, milliseconds.toInt());
        } else if (action == "stop_recording") {
            adsCtrl->stopRecording();
        }
        
        // Pagina segnali reali con grafico leggero
        String html = "<!DOCTYPE html><html><head>";
        html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'>";
        html += "<title>Multiplex - " + signalType + "</title>";
        html += "<style>";
        html += "body{font-family:Arial;margin:10px;text-align:center;background:#f5f5f5;}";
        html += ".container{max-width:900px;margin:0 auto;background:white;padding:20px;border-radius:10px;box-shadow:0 2px 10px rgba(0,0,0,0.1);}";
        html += ".value{font-size:26px;margin:15px 0;padding:20px;background:linear-gradient(135deg,#667eea 0%,#764ba2 100%);color:white;border-radius:10px;}";
        html += ".graph{width:100%;height:350px;border:2px solid #ddd;border-radius:8px;margin:20px 0;background:white;}";
        html += ".controls{margin:15px 0;padding:15px;background:#f9f9f9;border-radius:8px;}";
        html += ".btn{padding:12px 24px;margin:8px;background:#4CAF50;color:white;border:none;border-radius:6px;cursor:pointer;font-size:14px;}";
        html += ".btn:hover{background:#45a049;}.btn.stop{background:#f44336;}.btn.stop:hover{background:#da190b;}";
        html += ".status{margin:10px;padding:8px;border-radius:5px;font-weight:bold;}";
        html += ".recording{background:#d4edda;color:#155724;}.stopped{background:#f8d7da;color:#721c24;}";
        html += ".links{margin-top:20px;}";
        html += ".links a{padding:10px 20px;background:#2196F3;color:white;text-decoration:none;border-radius:5px;margin:5px;display:inline-block;}";
        html += "</style></head><body>";
        html += "<div class='container'>";
        html += "<h1>📊 " + signalType + "</h1>";
        html += "<div class='value' id='currentValue'> </div>";
        
        html += "<canvas class='graph' id='chart' width='850' height='350'></canvas>";
        
        html += "<div class='controls'>";
        html += "<h3>Recording Controls</h3>";
        html += "<button class='btn' onclick='startRecording()'>▶️ Start Recording</button>";
        html += "<button class='btn stop' onclick='stopRecording()'>⏹️ Stop Recording</button>";
        html += "<div id='status' class='status stopped'>Recording Stopped</div>";
        html += "</div>";
        
        html += "<div class='links'>";
        html += "<a href='/ADS_history'>📈 View History</a>";
        html += "<a href='/multiplex_config'>⚙️ Config</a>";
        html += "<a href='/uscite?signalType=" + signalType + "'>📤​ Uscite</a>";
        html += "</div>";
        html += "</div>";
        
        // JavaScript ottimizzato per grafico leggero
        html += "<script>";
        html += "let graphData=[],isRecording=false;";
        html += "const canvas=document.getElementById('chart'),ctx=canvas.getContext('2d');";
        html += "function drawChart(){";
        html += "ctx.clearRect(0,0,canvas.width,canvas.height);";
        html += "if(graphData.length<2){ctx.fillStyle='#999';ctx.font='16px Arial';ctx.textAlign='center';";
        html += "ctx.fillText('Waiting for data...',canvas.width/2,canvas.height/2);return;}";
        html += "const maxVal=Math.max(...graphData),minVal=Math.min(...graphData),range=maxVal-minVal||1;";
        html += "const stepX=canvas.width/(graphData.length-1),padding=30;";
        html += "ctx.strokeStyle='#4CAF50';ctx.lineWidth=3;ctx.beginPath();";
        html += "graphData.forEach((val,i)=>{";
        html += "const x=i*stepX,y=canvas.height-padding-((val-minVal)/range)*(canvas.height-2*padding);";
        html += "i===0?ctx.moveTo(x,y):ctx.lineTo(x,y);});";
        html += "ctx.stroke();";
        html += "ctx.fillStyle='#333';ctx.font='14px Arial';ctx.textAlign='left';";
        html += "ctx.fillText('Max: '+maxVal.toFixed(2),10,20);";
        html += "ctx.fillText('Min: '+minVal.toFixed(2),10,canvas.height-10);";
        html += "ctx.textAlign='right';";
        html += "ctx.fillText('Points: '+graphData.length,canvas.width-10,20);}";
        html += "function updateValue(){";
        html += "fetch('/getMultiplexValue?signalType=" + signalType + "')";
        html += ".then(r=>r.ok?r.json():Promise.reject('Error'))";
        html += ".then(d=>{";
        html += "document.getElementById('currentValue').innerHTML='<strong>'+d.value.toFixed(3)+'</strong><br><small>" + signalType + "</small>';";
        html += "if(isRecording){graphData.push(d.value);if(graphData.length>100)graphData.shift();drawChart();}";
        html += "}).catch(e=>{document.getElementById('currentValue').innerHTML='<span style=\"color:#ff6b6b;\">Error reading</span>';});}";
        html += "function startRecording(){";
        html += "fetch('/multiplex_graph?signalType=" + signalType + "&action=start_recording&milliseconds=1000')";
        html += ".then(()=>{isRecording=true;graphData=[];document.getElementById('status').className='status recording';";
        html += "document.getElementById('status').textContent='Recording Active ✅';});}";
        html += "function stopRecording(){";
        html += "fetch('/multiplex_graph?signalType=" + signalType + "&action=stop_recording')";
        html += ".then(()=>{isRecording=false;document.getElementById('status').className='status stopped';";
        html += "document.getElementById('status').textContent='Recording Stopped ⏹️';});}";
        html += "setInterval(updateValue,2000);updateValue();drawChart();";
        html += "</script></body></html>";
        
        request->send(200, "text/html", html);
    });

    server.on("/ADS_history", HTTP_GET, [](AsyncWebServerRequest *request) {
        String htmlContent = viewADSHistory::generateHTML();
        request->send(200, "text/html", htmlContent);
    });

    server.on("/getADSValuesHistory", HTTP_GET, [](AsyncWebServerRequest *request) {
        String content = viewADSHistory::adsContent();
        request->send(200, "text/html", content);
    });

    server.on("/deleteADSValue", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("index")) {
            int index = request->getParam("index")->value().toInt();
            ADS1115_controller::getInstance()->deleteRecordedValue(index);
        }
        request->redirect("/ADS_history");
    });
}
