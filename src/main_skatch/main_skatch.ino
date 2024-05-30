#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <esp_task_wdt.h>
#include <vector>

// Default WiFi credentials
const char* defaultSSID = "AmpliFi Alien";
const char* defaultPassword = "mekxedsymtecZikxu7";

// Variables to store WiFi credentials
String ssid = "";
String password = "";

// Log storage
String logEntries = "";

WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;
String ipAddress;

// Variables to store CPU load data
unsigned long lastMeasureTime = 0;
float cpuLoad = 0.0;

// Dummy data for measurements
struct Measurement {
  int id;
  String name;
  float value;
};

std::vector<Measurement> measurements;
int nextMeasurementId = 1;

// Function to format LittleFS - System Stability
void formatLittleFS() {
  Serial.println("Formatting LittleFS...");
  if (!LittleFS.format()) {
    Serial.println("LittleFS formatting failed!");
  } else {
    Serial.println("LittleFS formatted successfully.");
  }
}

// Function to read WiFi configuration from LittleFS - System Stability
void readWiFiConfig(String &ssid, String &password) {
  File configFile = LittleFS.open("/wifi_config.txt", "r");
  if (configFile) {
    ssid = configFile.readStringUntil('\n');
    password = configFile.readStringUntil('\n');
    configFile.close();
    ssid.trim();
    password.trim();
    Serial.println("Config read: SSID: " + ssid + " Password: " + password);
  } else {
    Serial.println("Failed to open WiFi config file.");
  }
}

// Function to save WiFi configuration to LittleFS - System Stability
void saveWiFiConfig(const String &ssid, const String &password) {
  File configFile = LittleFS.open("/wifi_config.txt", "w");
  if (configFile) {
    configFile.println(ssid);
    configFile.println(password);
    configFile.close();
    Serial.println("Config saved: SSID: " + ssid + " Password: " + password);
  } else {
    Serial.println("Failed to open WiFi config file for writing.");
  }
}

// Function to clear WiFi configuration from LittleFS - System Stability
void clearWiFiConfig() {
  LittleFS.remove("/wifi_config.txt");
  Serial.println("WiFi config cleared.");
}

// Function to connect to WiFi - System Stability
bool connectToWiFi(const char* ssid, const char* password) {
  WiFi.disconnect(true); // Disconnect and reset WiFi
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi: ");
  Serial.print(ssid);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 30000) { // 30 seconds timeout
    delay(1000);
    Serial.print(".");
    esp_task_wdt_reset(); // Reset the watchdog timer
  }

  if (WiFi.status() == WL_CONNECTED) {
    ipAddress = WiFi.localIP().toString();
    Serial.println();
    Serial.println("Connected to WiFi: " + ipAddress);
    return true;
  } else {
    Serial.println();
    Serial.println("Failed to connect to WiFi");
    return false;
  }
}

// Function to start Captive Portal for WiFi configuration - Initial WiFi Setup
void startCaptivePortal() {
  WiFi.softAP("ESP32-Setup");
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  ipAddress = WiFi.softAPIP().toString();

  server.on("/", HTTP_GET, []() {
    String html = "<html><head><title>ESP32 Captive Portal</title><style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; }";
    html += "form { display: inline-block; text-align: left; }";
    html += "label { display: block; margin: 10px 0 5px; }";
    html += "input[type='text'] { width: 200px; padding: 5px; }";
    html += "input[type='submit'] { padding: 5px 10px; margin-top: 10px; }";
    html += "</style></head><body>";
    html += "<h1>ESP32 Captive Portal</h1>";
    html += "<form action='/save' method='POST'>";
    html += "<label for='ssid'>SSID:</label><input type='text' name='ssid' id='ssid'><br>";
    html += "<label for='password'>Password:</label><input type='text' name='password' id='password'><br>";
    html += "<input type='submit' value='Save'>";
    html += "</form>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/save", HTTP_POST, []() {
    String newSSID = server.arg("ssid");
    String newPassword = server.arg("password");
    if (newSSID.length() > 0 && newPassword.length() > 0) {
      saveWiFiConfig(newSSID, newPassword);
      server.send(200, "text/html", "Configuration saved. Rebooting...");
      delay(3000);
      ESP.restart();
    } else {
      server.send(400, "text/html", "Invalid parameters.");
    }
  });

  server.begin();
  Serial.println("Captive Portal started!");
  Serial.println("Connect to the ESP32 at: http://" + ipAddress);
}

// Function to log system events with timestamp - System Stability
void logEvent(const String &event) {
  String timestamp = "[" + String(millis() / 1000) + "s] "; // Add timestamp
  logEntries += timestamp + event + "<br>";
  Serial.println(timestamp + event);
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait a second to ensure serial connection is initialized
  logEvent("ESP32 started and ready!");

  if (!LittleFS.begin()) {
    logEvent("An error has occurred while mounting LittleFS, attempting to format...");
    formatLittleFS();
    if (!LittleFS.begin()) {
      logEvent("Failed to mount LittleFS after formatting.");
      return;
    }
  }
  logEvent("LittleFS started!");

  // Dummy data initialization
  measurements.push_back({nextMeasurementId++, "Temperature", 22.5});
  measurements.push_back({nextMeasurementId++, "Humidity", 55.0});
  measurements.push_back({nextMeasurementId++, "Pressure", 1013.0});

  readWiFiConfig(ssid, password);
  if (ssid.isEmpty() || password.isEmpty()) {
    logEvent("No WiFi configuration found. Starting Captive Portal.");
    startCaptivePortal();
  } else if (!connectToWiFi(ssid.c_str(), password.c_str())) {
    logEvent("Connection to custom WiFi failed...Connecting to default WiFi");
    if (!connectToWiFi(defaultSSID, defaultPassword)) {
      logEvent("Failed to connect to default WiFi, starting Captive Portal");
      startCaptivePortal();
    }
  }

  setupServer();
}

void loop() {
  // Reset the watchdog timer
  esp_task_wdt_reset();

  if (WiFi.status() != WL_CONNECTED) {
    dnsServer.processNextRequest();
  }

  // Simulate CPU load measurement
  if (millis() - lastMeasureTime > 1000) {
    lastMeasureTime = millis();
    cpuLoad = random(10, 80); // Simulate a CPU load between 10% and 80%
  }
  server.handleClient();
  delay(10); // Add small delay to reset watchdog timer

  // Log system status every 25 seconds
  static unsigned long lastLogTime = 0;
  if (millis() - lastLogTime > 25000) {
    lastLogTime = millis();
    logEvent("System running normally. CPU load: " + String(cpuLoad) + "%");
  }
}

// Function to setup the web server and define routes - System Configuration and Usability
void setupServer() {
  server.on("/", HTTP_GET, []() {
    String html = "<html><head><title>ESP32 Configuration Page</title><style>";
    html += "body { font-family: Arial, sans-serif; }";
    html += "h1 { color: #333; }";
    html += "nav a { margin: 0 15px; text-decoration: none; color: #00f; }";
    html += "nav a:hover { text-decoration: underline; }";
    html += "</style></head><body>";
    html += "<h1>ESP32 Configuration Page</h1>";
    html += "<p>IP Address: " + ipAddress + "</p>";
    html += "<nav><a href='/graph'>Graph</a><a href='/wifi'>WiFi Settings</a>";
    html += "<a href='/measurements'>Measurements</a><a href='/log'>Log</a><a href='/analytics'>Analytics</a></nav>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/configure", HTTP_POST, []() {
    String newSSID = server.arg("ssid");
    String newPassword = server.arg("password");
    if (newSSID.length() > 0 && newPassword.length() > 0) {
      saveWiFiConfig(newSSID, newPassword);
      server.send(200, "text/html", "Configuration saved. Rebooting...");
      delay(3000);
      ESP.restart();
    } else {
      server.send(400, "text/html", "Invalid parameters.");
    }
  });

  server.on("/graph", HTTP_GET, []() {
    String html = "<html><head><title>CPU Load Graph</title><style>";
    html += "body { font-family: Arial, sans-serif; }";
    html += "h1 { color: #333; }";
    html += "</style></head><body>";
    html += "<h1>CPU Load Graph</h1>";
    html += "<canvas id='cpuLoadChart' width='400' height='200'></canvas>";
    html += "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>";
    html += "<script>";
    html += "var ctx = document.getElementById('cpuLoadChart').getContext('2d');";
    html += "var cpuLoadChart = new Chart(ctx, {";
    html += "type: 'line',";
    html += "data: { labels: [], datasets: [{ label: 'CPU Load', data: [] }] },";
    html += "options: { scales: { x: { title: { display: true, text: 'Time (s)' } }, y: { title: { display: true, text: 'CPU Load (%)' } } } }";
    html += "});";
    html += "function updateChart() { fetch('/cpu_load').then(response => response.json()).then(data => {";
    html += "cpuLoadChart.data.labels.push(data.time);";
    html += "cpuLoadChart.data.datasets[0].data.push(data.load);";
    html += "cpuLoadChart.update();";
    html += "setTimeout(updateChart, 1000);";
    html += "});";
    html += "}";
    html += "updateChart();";
    html += "</script>";
    html += "<button onclick='window.location.href=\"/\"'>Back to Mainpage</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/cpu_load", HTTP_GET, []() {
    String json = "{\"time\": " + String(millis() / 1000) + ", \"load\": " + String(cpuLoad) + "}";
    server.send(200, "application/json", json);
  });

  server.on("/wifi", HTTP_GET, []() {
    String html = "<html><head><title>WiFi Settings</title><style>";
    html += "body { font-family: Arial, sans-serif; text-align: center; }";
    html += "form { display: inline-block; text-align: left; margin-top: 20px; }";
    html += "label { display: block; margin: 10px 0 5px; }";
    html += "input[type='text'], input[type='file'] { width: 200px; padding: 5px; }";
    html += "input[type='submit'], button { padding: 5px 10px; margin-top: 10px; width: 100%; }";
    html += "form { margin-bottom: 20px; }";
    html += "</style></head><body>";
    html += "<h1>WiFi Settings</h1>";
    html += "<form action='/configure' method='POST'>";
    html += "<label for='ssid'>SSID:</label><input type='text' name='ssid' id='ssid'><br>";
    html += "<label for='password'>Password:</label><input type='text' name='password' id='password'><br>";
    html += "<input type='submit' value='Save'>";
    html += "</form>";
    html += "<form action='/reset_wifi' method='POST'>";
    html += "<input type='submit' value='Reset WIFI'>";
    html += "</form>";
    html += "<form action='/export_wifi' method='GET'>";
    html += "<input type='submit' value='Export WiFi Config'>";
    html += "</form>";
    html += "<form action='/import_wifi' method='POST' enctype='multipart/form-data'>";
    html += "<input type='file' name='wifi_config'><br>";
    html += "<input type='submit' value='Import WiFi Config'>";
    html += "</form>";
    html += "<button onclick='window.location.href=\"/\"'>Back to Mainpage</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/reset_wifi", HTTP_POST, []() {
    clearWiFiConfig();
    server.send(200, "text/html", "WiFi configuration cleared. Rebooting...");
    delay(3000);
    ESP.restart();
  });

  server.on("/export_wifi", HTTP_GET, []() {
    File configFile = LittleFS.open("/wifi_config.txt", "r");
    if (configFile) {
      String content = configFile.readString();
      configFile.close();
      server.sendHeader("Content-Type", "text/plain");
      server.sendHeader("Content-Disposition", "attachment; filename=wifi_config.txt");
      server.send(200, "text/plain", content);
    } else {
      server.send(500, "text/plain", "Failed to read WiFi config file.");
    }
  });

  server.on("/import_wifi", HTTP_POST, []() {
    if (server.upload().status == UPLOAD_FILE_START) {
      String filename = "/wifi_config.txt";
      if (LittleFS.exists(filename)) {
        LittleFS.remove(filename);
      }
      File file = LittleFS.open(filename, "w");
      if (!file) {
        server.send(500, "text/plain", "Failed to open file for writing.");
        return;
      }
      file.close();
    } else if (server.upload().status == UPLOAD_FILE_WRITE) {
      if (File file = LittleFS.open("/wifi_config.txt", "a")) {
        file.write(server.upload().buf, server.upload().currentSize);
        file.close();
      } else {
        server.send(500, "text/plain", "Failed to write to file.");
        return;
      }
    } else if (server.upload().status == UPLOAD_FILE_END) {
      server.send(200, "text/plain", "File uploaded successfully.");
    } else {
      server.send(500, "text/plain", "Failed to upload file.");
    }
  });

  server.on("/measurements", HTTP_GET, []() {
    String html = "<html><head><title>Measurements</title><style>";
    html += "body { font-family: Arial, sans-serif; }";
    html += "h1 { color: #333; }";
    html += "table { width: 100%; border-collapse: collapse; margin-top: 20px; }";
    html += "table, th, td { border: 1px solid #ddd; }";
    html += "th, td { padding: 8px; text-align: left; }";
    html += "th { background-color: #f2f2f2; }";
    html += "</style></head><body>";
    html += "<h1>Measurements</h1>";
    html += "<table><tr><th>ID</th><th>Name</th><th>Value</th><th>Action</th></tr>";
    for (auto& measurement : measurements) {
      html += "<tr><td>" + String(measurement.id) + "</td><td>" + measurement.name + "</td><td>" + String(measurement.value) + "</td>";
      html += "<td><a href='/edit_measurement?id=" + String(measurement.id) + "'>Edit</a> ";
      html += "<a href='/delete_measurement?id=" + String(measurement.id) + "'>Delete</a></td></tr>";
    }
    html += "</table>";
    html += "<h2>Add Measurement</h2>";
    html += "<form action='/add_measurement' method='POST'>";
    html += "<label for='name'>Name:</label><input type='text' name='name' id='name'><br>";
    html += "<label for='value'>Value:</label><input type='text' name='value' id='value'><br>";
    html += "<input type='submit' value='Add'>";
    html += "</form>";
    html += "<button onclick='window.location.href=\"/\"'>Back to Mainpage</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/add_measurement", HTTP_POST, []() {
    String name = server.arg("name");
    float value = server.arg("value").toFloat();
    if (name.length() > 0 && value > 0) {
      Measurement newMeasurement = {nextMeasurementId++, name, value};
      measurements.push_back(newMeasurement);
      server.send(200, "text/html", "Measurement added. <a href='/measurements'>Back to Measurements</a>");
    } else {
      server.send(400, "text/html", "Invalid parameters. <a href='/measurements'>Back to Measurements</a>");
    }
  });

  server.on("/edit_measurement", HTTP_GET, []() {
    int id = server.arg("id").toInt();
    Measurement* measurement = nullptr;
    for (auto& m : measurements) {
      if (m.id == id) {
        measurement = &m;
        break;
      }
    }

    if (measurement) {
      String html = "<html><head><title>Edit Measurement</title><style>";
      html += "body { font-family: Arial, sans-serif; }";
      html += "h1 { color: #333; }";
      html += "</style></head><body>";
      html += "<h1>Edit Measurement</h1>";
      html += "<form action='/update_measurement' method='POST'>";
      html += "<input type='hidden' name='id' value='" + String(measurement->id) + "'>";
      html += "<label for='name'>Name:</label><input type='text' name='name' id='name' value='" + measurement->name + "'><br>";
      html += "<label for='value'>Value:</label><input type='text' name='value' id='value' value='" + String(measurement->value) + "'><br>";
      html += "<input type='submit' value='Update'>";
      html += "</form>";
      html += "<button onclick='window.location.href=\"/\"'>Back to Mainpage</button>";
      html += "</body></html>";
      server.send(200, "text/html", html);
    } else {
      server.send(404, "text/html", "Measurement not found. <a href='/measurements'>Back to Measurements</a>");
    }
  });

  server.on("/update_measurement", HTTP_POST, []() {
    int id = server.arg("id").toInt();
    String name = server.arg("name");
    float value = server.arg("value").toFloat();
    Measurement* measurement = nullptr;
    for (auto& m : measurements) {
      if (m.id == id) {
        measurement = &m;
        break;
      }
    }

    if (measurement && name.length() > 0 && value > 0) {
      measurement->name = name;
      measurement->value = value;
      server.send(200, "text/html", "Measurement updated. <a href='/measurements'>Back to Measurements</a>");
    } else {
      server.send(400, "text/html", "Invalid parameters or measurement not found. <a href='/measurements'>Back to Measurements</a>");
    }
  });

  server.on("/delete_measurement", HTTP_GET, []() {
    int id = server.arg("id").toInt();
    auto it = std::find_if(measurements.begin(), measurements.end(), [id](Measurement& m) { return m.id == id; });

    if (it != measurements.end()) {
      measurements.erase(it);
      server.send(200, "text/html", "Measurement deleted. <a href='/measurements'>Back to Measurements</a>");
    } else {
      server.send(404, "text/html", "Measurement not found. <a href='/measurements'>Back to Measurements</a>");
    }
  });

  // Route for log page - System Stability
  server.on("/log", HTTP_GET, []() {
    String html = "<html><head><title>System Log</title><style>";
    html += "body { font-family: Arial, sans-serif; }";
    html += "h1 { color: #333; }";
    html += "</style></head><body>";
    html += "<h1>System Log</h1>";
    html += "<div id='log'>" + logEntries + "</div>";
    html += "<button onclick='exportLog()'>Export Log</button>";
    html += "<script>";
    html += "function updateLog() { fetch('/get_log').then(response => response.text()).then(data => {";
    html += "document.getElementById('log').innerHTML = data;";
    html += "setTimeout(updateLog, 25000);"; // Updated to 25 seconds
    html += "});";
    html += "}";
    html += "function exportLog() {";
    html += "fetch('/export_log').then(response => response.blob()).then(blob => {";
    html += "var url = window.URL.createObjectURL(blob);";
    html += "var a = document.createElement('a');";
    html += "a.style.display = 'none';";
    html += "a.href = url;";
    html += "a.download = 'log.txt';";
    html += "document.body.appendChild(a);";
    html += "a.click();";
    html += "window.URL.revokeObjectURL(url);";
    html += "});";
    html += "}";
    html += "updateLog();";
    html += "</script>";
    html += "<button onclick='window.location.href=\"/\"'>Back to Mainpage</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/get_log", HTTP_GET, []() {
    server.send(200, "text/plain", logEntries);
  });

  server.on("/export_log", HTTP_GET, []() {
    server.sendHeader("Content-Type", "text/plain");
    server.sendHeader("Content-Disposition", "attachment; filename=log.txt");
    server.send(200, "text/plain", logEntries);
  });

  // Route for analytics page - Real-time Data Display
  server.on("/analytics", HTTP_GET, []() {
    String html = "<html><head><title>Analytics</title><style>";
    html += "body { font-family: Arial, sans-serif; }";
    html += "h1 { color: #333; }";
    html += "</style></head><body>";
    html += "<h1>Real-time Data Analytics</h1>";
    html += "<div id='analyticsData'>Loading data...</div>";
    html += "<script>";
    html += "function updateAnalytics() { fetch('/analytics_data').then(response => response.json()).then(data => {";
    html += "document.getElementById('analyticsData').innerHTML = 'Time: ' + data.time + 's, CPU Load: ' + data.cpuLoad + '%';";
    html += "setTimeout(updateAnalytics, 1000);";
    html += "});";
    html += "}";
    html += "updateAnalytics();";
    html += "</script>";
    html += "<button onclick='window.location.href=\"/\"'>Back to Mainpage</button>";
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/analytics_data", HTTP_GET, []() {
    String json = "{\"time\": " + String(millis() / 1000) + ", \"cpuLoad\": " + String(cpuLoad) + "}";
    server.send(200, "application/json", json);
  });

  server.begin();
  logEvent("Webserver started!");
  logEvent("Server started. You can connect to the ESP32 at: http://" + ipAddress);
}

