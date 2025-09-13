#include "WebServerManager.h"
#include <vector>

struct DataItem {
    int id;
    String startRegister;
    int length;
    String type;
    String rw;
    String label;
    String description;
    String unit;
};

std::vector<DataItem> dataItems = {
    {1, "100", 2, "Float", "Read Only", "V12", "Linked Voltage Phase 1-2", "V"},
    {2, "102", 2, "Float", "Read Only", "V23", "Linked Voltage Phase 2-3", "V"},
    {3, "104", 2, "Float", "Read Only", "V31", "Linked Voltage Phase 3-1", "V"},
    {4, "158", 2, "Float", "Read Only", "Temperature", "Temperature (internal probe)", "Celsius"},
    {5, "165", 1, "Int", "Read Only", "Alarm 1", "Alarm 1 state", "-"},
    {6, "308", 2, "Float", "Read/Write", "VTP", "VT primary voltage value", "V"},
};
int dataItemCount = sizeof(dataItems) / sizeof(DataItem);

WebServerManager::WebServerManager(const char *ssid, const char *password, bool &master, bool &swap)
    : default_ssid(ssid), default_password(password), master(master), swap(swap), server(80) {}

void WebServerManager::begin(ModbusRTUMaster &modbus) {
    modbusMaster = &modbus;
    ssid_ap = default_ssid;
    password_ap = default_password;

    if (WiFi.softAP(ssid_ap.c_str(), password_ap.c_str())) {
        Serial.println("AP correctly started");
    } else {
        Serial.println("Error on start AP");
        while (true);
    }

    dnsServer.start(53, "*", WiFi.softAPIP());

    server.on("/setWifi", HTTP_POST, [this]() { handleWifiConfig(); });
    server.on("/config", HTTP_GET, [this]() { handleDataPage(); });
    server.on("/readRegister", HTTP_GET, [this]() { handleReadRegister(); });
    server.on("/addData", HTTP_POST, [this]() { handleAddData(); });
    server.on("/deleteData", HTTP_POST, [this]() { handleDeleteData(); }); 
    server.on("/updateData", HTTP_POST, [this]() { handleUpdateData(); });
    server.on("/toggleMaster", HTTP_POST, [this]() { handleToggleMaster(); });
    server.on("/toggleSwap", HTTP_POST, [this]() { handleToggleSwap(); });

    server.onNotFound([this]() { handleRoot(); });

    server.begin();
    Serial.println("Server started");
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
}

void WebServerManager::handleClient() {
    dnsServer.processNextRequest();
    server.handleClient();
}

void WebServerManager::handleRoot() {
    String options = "";
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
        options += "<option value=\"" + WiFi.SSID(i) + "\">" + WiFi.SSID(i) + "</option>";
    }
    String page = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <body>
          <h1>WiFi Configuration</h1>
          <form action="/setWifi" method="POST">
            <label for="ssid">SSID:</label>
            <select id="ssid" name="ssid">
              %OPTIONS%
            </select><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Submit">
          </form>
        </body>
        </html>
        )rawliteral";
    page.replace("%OPTIONS%", options);
    server.send(200, "text/html", page);
}

void WebServerManager::handleWifiConfig() {
    String new_ssid = server.arg("ssid");
    String new_password = server.arg("password");

    if (new_ssid.length() > 0 && new_password.length() > 0) {
        ssid_ap = new_ssid;
        password_ap = new_password;

        WiFi.begin(ssid_ap.c_str(), password_ap.c_str());

        int timeout = 0;
        while (WiFi.status() != WL_CONNECTED && timeout < 20) {
            delay(500);
            Serial.print(".");
            timeout++;
        }

        if (WiFi.status() == WL_CONNECTED) {
            String successPage = R"rawliteral(
              <!DOCTYPE html>
              <html>
              <head>
                <title>Successful connection</title>
                <style>
                  body {
                    font-family: Arial, sans-serif;
                    text-align: center;
                    padding: 50px;
                  }
                  h1 {
                    color: #4CAF50;
                  }
                  p {
                    font-size: 18px;
                  }
                </style>
              </head>
              <body>
                <h1>Congratulations!</h1>
                <p>You are successfully connected.</p>
                <p>This is the IP address to access the web server that exposes the data:</p>
                <p><strong>%IP_ADDRESS%</strong></p>
              </body>
              </html>
              )rawliteral";

            successPage.replace("%IP_ADDRESS%", WiFi.localIP().toString());
            dnsServer.stop();
            server.send(200, "text/html", successPage);
            Serial.println("Successful connection!");
            Serial.print("IP: ");
            Serial.println(WiFi.localIP());
        } else {
            server.send(200, "text/plain", "Connection Failed!");
            Serial.println("Connection Failed!");
        }
    } else {
        server.send(200, "text/plain", "Invalid SSID or password.");
    }
}

void WebServerManager::handleDataPage() {
    String checkedMasterAttribute = master ? "checked" : "";
    String checkedSwapAttribute = swap ? "checked" : "";

    String dataPage = R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <title>Config page</title>
        <style>
          .modal-dialog-centered {
            display: flex;
            align-items: center;
            min-height: calc(100% - 1rem);
          }
        </style>
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css">
        <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.8.0/Chart.bundle.min.js"></script>

      </head>
      <body class="d-flex justify-content-center align-items-start">
      <section style="width: 100%;padding: 20px;margin-top: 32px;">
        <div class="container">
        <h1>Welcome to the configuration page</h1>
         <div class="form-check form-switch" style="margin: 32px 0;">
            <input class="form-check-input" type="checkbox" id="formCheck-1" style="border-width: 1px;" onchange="toggleMaster()" %INITIAL_CHECKED_MASTER%>
            <label class="form-check-label" for="formCheck-1">Master Mode</label>
          </div>
          <div class="form-check form-switch" style="margin: 32px 0;">
            <input class="form-check-input" type="checkbox" id="formCheck-2" style="border-width: 1px;" onchange="toggleSwap()" %INITIAL_CHECKED_SWAP%>
            <label class="form-check-label" for="formCheck-1">Swap configuration</label>
          </div>
        
        <div class="table-responsive" style="margin-bottom: 0px;">
          <table id="data-table" class="table table-striped table-hover table-bordered">
          <thead class="table-dark">
            <tr>
              <th style="font-style:italic; text-align:center; text-decoration:underline;">ID</th>
              <th style="font-style:italic; text-align:center;">Start Register</th>
              <th style="font-style:italic; text-align:center;">Length</th>
              <th style="font-style:italic; text-align:center;">Type</th>
              <th style="font-style:italic; text-align:center;">R/W</th>
              <th style="font-style:italic; text-align:center;">Label</th>
              <th style="font-style:italic; text-align:center;">Description</th>
              <th style="font-style:italic; text-align:center;">Unit</th>
              <th style="font-style:italic; text-align:center;">Action</th>
            </tr>
          </thead>
          <tbody>
    )rawliteral";

    for (const auto& item : dataItems) {
        dataPage += "<tr id= \"row-" + String(item.id) + "\">";
        dataPage += "<td style=\"text-align:center;\">" + String(item.id) + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + item.startRegister + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + String(item.length) + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + item.type + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + item.rw + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + item.label + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + item.description + "</td>";
        dataPage += "<td style=\"text-align:center;\">" + item.unit + "</td>";
        dataPage += "<td class=\"action-btns\">";
        dataPage += "<div class=\"d-flex justify-content-center align-items-center\" style=\"width: 100%;\">";
        dataPage += "<div class=\"btn-group\" role=\"group\">";
        dataPage += "<button class=\"btn btn-primary analytics\" type=\"button\" style=\"background: green;border-width: 0px;font-weight: bold;border-radius: 12px;margin: 0 6px;\" data-bs-target=\"#modal-2\" data-bs-toggle=\"modal\" data-register=\"" + item.startRegister + "\" data-length=\"" + String(item.length) + "\" data-type=\"" + item.type + "\" data-unit=\"" + item.unit + "\"><svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1em\" height=\"1em\" fill=\"currentColor\" viewBox=\"0 0 16 16\" class=\"bi bi-bar-chart-line-fill\" style=\"font-size: 20px;padding: 0px;\"><path d=\"M11 2a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v12h.5a.5.5 0 0 1 0 1H.5a.5.5 0 0 1 0-1H1v-3a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v3h1V7a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v7h1z\"></path></svg></button>";

        dataPage += "<button class=\"btn btn-primary\" type=\"button\" style=\"background: orange;border-width: 0px;font-weight: bold;margin: 0 6px;border-radius: 12px;\" onclick=\"editData(" + String(item.id) + ", '" 
        + item.startRegister + "', "
        + String(item.length) + ", '"
        + item.type + "', '" 
        + item.rw + "', '"
        + item.label + "', '" 
        + item.description + "', '" 
        + item.unit
        + "')\"><svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1em\" height=\"1em\" fill=\"currentColor\" viewBox=\"0 0 16 16\" class=\"bi bi-pencil-fill\" style=\"font-size: 20px;\"><path d=\"M12.854.146a.5.5 0 0 0-.707 0L10.5 1.793 14.207 5.5l1.647-1.646a.5.5 0 0 0 0-.708l-3-3zm.646 6.061L9.793 2.5 3.293 9H3.5a.5.5 0 0 1 .5.5v.5h.5a.5.5 0 0 1 .5.5v.5h.5a.5.5 0 0 1 .5.5v.5h.5a.5.5 0 0 1 .5.5v.207l6.5-6.5zm-7.468 7.468A.5.5 0 0 1 6 13.5V13h-.5a.5.5 0 0 1-.5-.5V12h-.5a.5.5 0 0 1-.5-.5V11h-.5a.5.5 0 0 1-.5-.5V10h-.5a.499.499 0 0 1-.175-.032l-.179.178a.5.5 0 0 0-.11.168l-2 5a.5.5 0 0 0 .65.65l5-2a.5.5 0 0 0 .168-.11l.178-.178z\"></path></svg></button>";

        dataPage += "</button><button class=\"btn btn-primary\" type=\"button\" style=\"background: red;border-width: 0px;font-weight: bold;border-radius: 12px;margin: 0 6px;\" onclick=\"deleteData(" + String(item.id) + ")\"><svg xmlns=\"http://www.w3.org/2000/svg\" width=\"1em\" height=\"1em\" fill=\"currentColor\" viewBox=\"0 0 16 16\" class=\"bi bi-eraser-fill\" style=\"font-size: 20px;\"><path d=\"M8.086 2.207a2 2 0 0 1 2.828 0l3.879 3.879a2 2 0 0 1 0 2.828l-5.5 5.5A2 2 0 0 1 7.879 15H5.12a2 2 0 0 1-1.414-.586l-2.5-2.5a2 2 0 0 1 0-2.828l6.879-6.879zm.66 11.34L3.453 8.254 1.914 9.793a1 1 0 0 0 0 1.414l2.5 2.5a1 1 0 0 0 .707.293H7.88a1 1 0 0 0 .707-.293l.16-.16z\"></path></svg></button>";

        dataPage += "</div>";
        dataPage += "</div>";
        dataPage += "</td>";
        dataPage += "</tr>";
      }

      dataPage += R"rawliteral(
          </tbody>
          </table>
          </div>
          </div>
          <div class="container">
              <div class="row">
                  <div class="col-md-12">
                      <div class="d-flex d-md-flex justify-content-end align-items-start justify-content-md-end align-items-md-end" style="margin-bottom: 24px;"><a class="btn btn-primary" role="button" style="padding: 8px;border-radius: 12px;border-width: 0px;width: 48px;height: 48px;" data-bs-target="#dataModal" data-bs-toggle="modal" href="#"><svg xmlns="http://www.w3.org/2000/svg" width="1em" height="1em" fill="currentColor" viewBox="0 0 16 16" class="bi bi-plus-lg" style="font-size: 32px;">
                                  <path fill-rule="evenodd" d="M8 2a.5.5 0 0 1 .5.5v5h5a.5.5 0 0 1 0 1h-5v5a.5.5 0 0 1-1 0v-5h-5a.5.5 0 0 1 0-1h5v-5A.5.5 0 0 1 8 2"></path>
                              </svg></a></div>
                  </div>
              </div>
          </div>
        </section>
        
        <div class="modal fade" id="dataModal" tabindex="-1" aria-labelledby="dataModalLabel" aria-hidden="true">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <h5 class="modal-title" id="dataModalLabel">Add New Data</h5>
                <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
              </div>
              <div class="modal-body">
                <form id="newDataForm">
                  <div class="mb-3">
                    <label for="register" class="form-label">Register</label>
                    <input type="text" class="form-control" id="register" placeholder="Register">
                  </div>
                  <div class="mb-3">
                    <label for="length" class="form-label">Length</label>
                    <input type="number" class="form-control" id="length" placeholder="Length">
                  </div>
                  <div class="mb-3">
                    <label for="type" class="form-label">Type</label>
                    <select id="type" for="type" class="form-select">
                      <option value="Float" selected="">Float</option>
                      <option value="Int">Int</option>
                      <option value="Long">Long</option>
                    </select>
                  </div>
                  <div class="mb-3">
                    <label for="readwrite" class="form-label">Read/Write</label>
                    <select id="readwrite" for="readwrite" class="form-select">
                      <option value="Read Only" selected="">Read Only</option>
                      <option value="Read/Write">Read/Write</option>
                    </select>
                  </div>
                  <div class="mb-3">
                    <label for="label" class="form-label">Label</label>
                    <input type="text" class="form-control" id="label" placeholder="Label">
                  </div>
                  <div class="mb-3">
                    <label for="description" class="form-label">Description</label>
                    <textarea class="form-control" id="description" rows="3" placeholder="Description"></textarea>
                  </div>
                  <div class="mb-3">
                    <label for="unit" class="form-label">Unit</label>
                    <input type="text" class="form-control" id="unit" placeholder="Unit">
                  </div>
                  <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                  <button type="button" class="btn btn-primary" onclick="saveNewData()">Save changes</button>
                </form>
              </div>
            </div>
          </div>
        </div>

        <div class="modal fade" id="editDataModal" tabindex="-1" aria-labelledby="editDataModalLabel" aria-hidden="true" role="dialog">
          <div class="modal-dialog" role="document">
            <div class="modal-content">
              <div class="modal-header">
                <h5 class="modal-title" id="editDataModalLabel">Edit Data</h5>
                <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
              </div>
              <div class="modal-body">
                <form id="editDataForm">
                  <input type="hidden" id="edit-id">
                  <div class="mb-3">
                    <label for="edit-register" class="form-label">Start Register</label>
                    <input type="text" class="form-control" id="edit-register" name="edit-register">
                  </div>
                  <div class="mb-3">
                    <label for="edit-length" class="form-label">Length</label>
                    <input type="number" class="form-control" id="edit-length" name="edit-length">
                  </div>
                  <div class="mb-3">
                    <label for="edit-type" class="form-label">Type</label>
                    <select id="edit-type" for="type" class="form-select">
                      <option value="Float" selected="">Float</option>
                      <option value="Int">Int</option>
                      <option value="Long">Long</option>
                    </select>
                  </div>
                  <div class="mb-3">
                    <label for="edit-readwrite" class="form-label">R/W</label>
                    <select id="edit-readwrite" for="edit-readwrite" class="form-select">
                      <option value="Read Only" selected="">Read Only</option>
                      <option value="Read/Write">Read/Write</option>
                    </select>
                  </div>
                  <div class="mb-3">
                    <label for="edit-label" class="form-label">Label</label>
                    <input type="text" class="form-control" id="edit-label" name="edit-label">
                  </div>
                  <div class="mb-3">
                    <label for="edit-description" class="form-label">Description</label>
                    <input type="text" class="form-control" id="edit-description" name="edit-description">
                  </div>
                  <div class="mb-3">
                    <label for="edit-unit" class="form-label">Unit</label>
                    <input type="text" class="form-control" id="edit-unit" name="edit-unit">
                  </div>
                  <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                  <button type="button" class="btn btn-primary" onclick="updateData()">Save changes</button>
                </form>
              </div>
            </div>
          </div>
        </div>

        <div class="modal fade" role="dialog" tabindex="-1" id="modal-2">
            <div class="modal-dialog modal-xl modal-dialog-centered" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                      <h5 id="last-value" class="modal-title"></h5>
                      <button class="btn-close" aria-label="Close" data-bs-dismiss="modal" type="button"></button>
                    </div>
                    <div class="modal-body">
                        <div class="container">
                            <div class="row">
                                <div class="col-md-12"><canvas id="analytics"></canvas></div>
                            </div>
                        </div>
                    </div>
                    <div class="modal-footer"><button class="btn btn-primary" id="modal-btn-download-data" type="submit" style="border-radius: 0;border-width: 0px;" onclick="downloadCSV()">Download Data</button></div>
                </div>
            </div>
        </div>

        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdn.jsdelivr.net/npm/popper.js@1.12.9/dist/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js"></script>
        <script>

          function toggleMaster() {
            var isChecked = document.getElementById("formCheck-1").checked;
            var xhr = new XMLHttpRequest();
            xhr.open("POST", "/toggleMaster", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            xhr.send("isChecked=" + isChecked);
          }

          function toggleSwap() {
            var isChecked = document.getElementById("formCheck-2").checked;
            var xhr = new XMLHttpRequest();
            xhr.open("POST", "/toggleSwap", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            xhr.send("isChecked=" + isChecked);
          }

          function saveNewData() {
            var form = document.getElementById("newDataForm");

            if(form.register.value == 0 && form.length.value == 0){
              alert("Please enter the register and length values.");
            }else if(form.register.value == 0){
              alert("Please enter the register value.");
            }else if(form.length.value == 0){
              alert("Please enter the length value.");
            }else{
              saveData();
              
              var newItem = {
                startRegister: form.register.value,
                length: form.length.value,
                type: form.type.value,
                rw: form.readwrite.value,
                label: form.label.value,
                description: form.description.value,
                unit: form.unit.value
              };

              var table = document.getElementById("data-table");
              var row = table.insertRow(-1);

              var cell1 = row.insertCell(0);
              var cell2 = row.insertCell(1);
              var cell3 = row.insertCell(2);
              var cell4 = row.insertCell(3);
              var cell5 = row.insertCell(4);
              var cell6 = row.insertCell(5);
              var cell7 = row.insertCell(6);
              var cell8 = row.insertCell(7);
              var cell9 = row.insertCell(8);

              
              cell1.innerHTML = newItem.id;
              cell2.innerHTML = newItem.startRegister;
              cell3.innerHTML = newItem.length;
              cell4.innerHTML = newItem.type;
              cell5.innerHTML = newItem.rw;
              cell6.innerHTML = newItem.label;
              cell7.innerHTML = newItem.description;
              cell8.innerHTML = newItem.unit;
              cell9.innerHTML = '<button class="action-btns show-btn" onclick="showDetails(this, \'' + newItem.startRegister + '\', \'' + newItem.length + '\')">Show</button><button class="edit-btn">Edit</button><button class="del-btn">Del</button>';

              cell8.classList.add('action-btns');

              $('#dataModal').modal('hide');
            }
          }

          function saveData() {
            var form = document.getElementById("newDataForm");
            var newItem = {
                startRegister: form.register.value,
                length: form.length.value,
                type: form.type.value,
                rw: form.readwrite.value,
                label: form.label.value,
                description: form.description.value,
                unit: form.unit.value
            };

            var xhr = new XMLHttpRequest();
            xhr.open("POST", "/addData", true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            var data = "register=" + encodeURIComponent(newItem.startRegister) +
                        "&length=" + encodeURIComponent(newItem.length) +
                        "&type=" + encodeURIComponent(newItem.type) +
                        "&readwrite=" + encodeURIComponent(newItem.rw) +
                        "&label=" + encodeURIComponent(newItem.label) +
                        "&description=" + encodeURIComponent(newItem.description) +
                        "&unit=" + encodeURIComponent(newItem.unit);

            xhr.onreadystatechange = function () {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    location.reload();
                }
            };

            xhr.send(data);
        }

        function deleteData(id) {
            if (confirm("Are you sure you want to delete this item?")) {
              var xhr = new XMLHttpRequest();
              xhr.open("POST", "/deleteData", true);
              xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
              xhr.onreadystatechange = function () {
                if (xhr.readyState == 4 && xhr.status == 200) {
                  location.reload();
                }
              };
              xhr.send("id=" + id);
            }
          }

          function editData(id, startRegister, length, type, rw, label, description, unit) {
              document.getElementById("edit-id").value = id;
              document.getElementById("edit-register").value = startRegister;
              document.getElementById("edit-length").value = length;
              document.getElementById("edit-type").value = type;
              document.getElementById("edit-readwrite").value = rw;
              document.getElementById("edit-label").value = label;
              document.getElementById("edit-description").value = description;
              document.getElementById("edit-unit").value = unit;

              $('#editDataModal').modal('show');
            }

          function updateData() {
            var form = document.getElementById("editDataForm");

            if(form["edit-register"].value == 0 && form["edit-length"].value == 0){
              alert("Please enter the register and length values.");
            }else if(form["edit-register"].value == 0){
              alert("Please enter the register value.");
            }else if(form["edit-length"].value == 0){
              alert("Please enter the length value.");
            }else{
              var updatedItem = {
                id: parseInt(form["edit-id"].value),
                startRegister: form["edit-register"].value,
                length: form["edit-length"].value,
                type: form["edit-type"].value,
                rw: form["edit-readwrite"].value,
                label: form["edit-label"].value,
                description: form["edit-description"].value,
                unit: form["edit-unit"].value
              }
              var xhr = new XMLHttpRequest()
              xhr.open("POST", "/updateData", true)
              xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
              var data = "id=" + encodeURIComponent(updatedItem.id) +
                        "&register=" + encodeURIComponent(updatedItem.startRegister) +
                        "&length=" + encodeURIComponent(updatedItem.length) +
                        "&type=" + encodeURIComponent(updatedItem.type) +
                        "&readwrite=" + encodeURIComponent(updatedItem.rw) +
                        "&label=" + encodeURIComponent(updatedItem.label) +
                        "&description=" + encodeURIComponent(updatedItem.description) +
                        "&unit=" + encodeURIComponent(updatedItem.unit);
              xhr.onreadystatechange = function () {
                if (xhr.readyState == 4 && xhr.status == 200) {
                  location.reload();
                }
              }
              xhr.send(data);
            }
          }

          function addData(chart, label, data, unit) {
            modalLastValue = document.getElementById('last-value');
        
            modalLastValue.textContent = "Last value: " + data + " " + unit;

            chart.data.labels.push(label);
            chart.data.datasets.forEach((dataset) => {
                dataset.data.push(data.toFixed(2))
                dataset.label = 'Unit of measurement:' + unit
            });
            chart.update()
          }
          
          const canvas = document.getElementById('analytics')
          const labels = []
          const data = {
              labels: labels,
              datasets: [{
                  label: 'Measuring',
                  backgroundColor: 'transparent',
                  borderColor: 'rgb(0, 0, 255)',
                  data: [],
                  pointStyle: 'circle',
                  pointBackgroundColor: 'rgba(0, 0, 255, 0.2)',
                  pointRadius: 10,
                  pointHoverRadius: 15
              }]
          };
          const config = {
              type: 'line',
              data: data,
              options: {
                  scales: {
                      y: {
                          ticks: {
                              callback: function(value) {
                                  return value.toFixed(2)
                              }
                          }
                      }
                  }
              } 
          };
          
          const myChart = new Chart(canvas, config)

          let intervaId
          
          function fetchDataAndUpdateChart(register, length, type, unit) {
            fetch(`/readRegister?start=${register}&length=${length}&type=${type}`)
                .then(response => response.json())
                .then(data => {
                    const registers = data.registers
                    if (registers && registers.length > 0) {
                        const currentTime = new Date()
                        const newData = registers[0]
                        addData(myChart, currentTime.getHours() + ":" + currentTime.getMinutes() + ":" + currentTime.getSeconds(), newData, unit)
                    }
                })
                .catch(error => console.error('Error fetching data:', error))
          }

          function resetChart(chart) {
            chart.data.labels = []
            chart.data.datasets.forEach((dataset) => {
                dataset.data = []
            });
            chart.update()
          }

          document.querySelectorAll('.btn.analytics').forEach(button => {
            button.addEventListener('click', (event) => {
                const register = event.currentTarget.getAttribute('data-register');
                const length = event.currentTarget.getAttribute('data-length');
                const type = event.currentTarget.getAttribute('data-type');
                const unit = event.currentTarget.getAttribute('data-unit');

                fetchDataAndUpdateChart(register, length, type, unit)
                intervalId = setInterval(() => fetchDataAndUpdateChart(register, length, type, unit), 5000) 
            });
          });

          document.getElementById('modal-2').addEventListener('hidden.bs.modal', () => {
              clearInterval(intervalId);
              resetChart(myChart);
          });

          function convertToCSV(chart) {
            let csv = 'Time,Value\n';
            chart.data.labels.forEach((label, index) => {
                const value = chart.data.datasets[0].data[index];
                csv += `${label},${value}\n`;
            });
            return csv;
          }

          function downloadCSV() {
              const csv = convertToCSV(myChart);
              const blob = new Blob([csv], { type: 'text/csv' });
              const url = window.URL.createObjectURL(blob);
              const a = document.createElement('a');
              a.setAttribute('href', url);
              a.setAttribute('download', 'TSM_IoT_Project_Work_data.csv');
              a.click();
              window.URL.revokeObjectURL(url);
          }

        </script>

      </body>
      </html>
    )rawliteral";

    dataPage.replace("%INITIAL_CHECKED_MASTER%", checkedMasterAttribute);
    dataPage.replace("%INITIAL_CHECKED_SWAP%", checkedSwapAttribute);

    server.send(200, "text/html", dataPage);
}

void WebServerManager::handleReadRegister() {
    String start = server.arg("start");
    String lengthStr = server.arg("length");
    String type = server.arg("type");

    unsigned long startRegisterLong = strtoul(start.c_str(), nullptr, 0);
    if (startRegisterLong > 65535) {
        Serial.println("Invalid start value");
        return;
    }
    uint16_t startRegister = static_cast<uint16_t>(startRegisterLong);

    unsigned long lengthLong = strtoul(lengthStr.c_str(), nullptr, 10);
    if (lengthLong > 65535 || lengthLong == 0) {
        Serial.println("Invalid length value");
        return;
    }
    uint16_t length = static_cast<uint16_t>(lengthLong);
    
    uint16_t holdingRegisters[2]; 
    bool success = modbusMaster->readHoldingRegisters(1, startRegister - 1, holdingRegisters, length);
    if (success) {
        String result = "{ \"registers\": [";
        for (int i = 0; i < length; i+=2) {
            if(type == "Float"){
              if(swap){
                result += String(convertToFloat(holdingRegisters[i+1], holdingRegisters[i]));
              }else{
                result += String(convertToFloat(holdingRegisters[i], holdingRegisters[i+1]));
              }
            }else if(type == "Int"){
              result += String(holdingRegisters[i]);
            }else if(type == "Long"){
              if(swap){
                result += String(holdingRegisters[i+1]);
              }else{
                result += String(holdingRegisters[i]);
              }
              
            }
        }
        result += "] }";
        server.send(200, "application/json", result);
    } else {
        server.send(500, "text/plain", "Failed to read register");
    }
}

void WebServerManager::handleToggleMaster() {
    if (server.hasArg("isChecked")) {
        master = server.arg("isChecked") == "true";
        server.send(200, "text/plain", "success");
    } else {
        server.send(400, "text/plain", "missing arguments");
    }
}

void WebServerManager::handleToggleSwap() {
    if (server.hasArg("isChecked")) {
        swap = server.arg("isChecked") == "true";
        server.send(200, "text/plain", "success");
    } else {
        server.send(400, "text/plain", "missing arguments");
    }
}

void WebServerManager::handleAddData() {
    if (server.hasArg("register") && server.hasArg("length") && server.hasArg("type") && server.hasArg("readwrite") && server.hasArg("label") && server.hasArg("description") && server.hasArg("unit")) {
        
        DataItem newItem;

        if (!dataItems.empty()) {
            DataItem lastItem = dataItems.back();
            newItem.id = lastItem.id + 1;
        }else{
            newItem.id = 0;
        }
        
        newItem.startRegister = server.arg("register");
        newItem.length = server.arg("length").toInt();
        newItem.type = server.arg("type");
        newItem.rw = server.arg("readwrite");
        newItem.label = server.arg("label");
        newItem.description = server.arg("description");
        newItem.unit = server.arg("unit");

        dataItems.push_back(newItem);

        server.send(200, "text/plain", "success");
    } else {
        server.send(400, "text/plain", "missing arguments");
    }
}

void WebServerManager::handleDeleteData() {
    if (server.hasArg("id")) {
        int idToDelete = server.arg("id").toInt();

        auto it = std::remove_if(dataItems.begin(), dataItems.end(), [idToDelete](const DataItem& item) {
            return item.id == idToDelete;
        });

        if (it != dataItems.end()) {
            dataItems.erase(it, dataItems.end());
            server.send(200, "text/plain", "success");
        } else {
            server.send(404, "text/plain", "not found");
        }
    } else {
        server.send(400, "text/plain", "missing id");
    }
}

void WebServerManager::handleUpdateData() {
  if (server.hasArg("id") && server.hasArg("register") && server.hasArg("length") && server.hasArg("type") && server.hasArg("readwrite") && server.hasArg("label") && server.hasArg("description") && server.hasArg("unit")) {
    int id = server.arg("id").toInt();

    auto it = std::find_if(dataItems.begin(), dataItems.end(), [id](const DataItem& item) {
      return item.id == id;
    });

    if (it != dataItems.end()) {
      it->startRegister = server.arg("register");
      it->length = server.arg("length").toInt();
      it->type = server.arg("type");
      it->rw = server.arg("readwrite");
      it->label = server.arg("label");
      it->description = server.arg("description");
      it->unit = server.arg("unit");

      server.send(200, "text/plain", "success");
    } else {
      server.send(404, "text/plain", "not found");
    }
  } else {
    server.send(400, "text/plain", "missing arguments");
  }
}

String WebServerManager::getSsid() {
    return ssid_ap;
}

String WebServerManager::getPassword() {
    return password_ap;
}
