#include "viewHistory.h"

String viewHistory::html = "";

String viewHistory::generateHTML()
{
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>History Register</title>";
    html += "<style>";
    html += viewGeneric::addCss();
    html += viewGeneric::addFormCss();
    html += viewGeneric::addNavbarCss();
    html += "</style>";
    html += "</head><body>";
    
    // Navbar sempre presente
    html += viewGeneric::addNavbar();
    
    html += viewGeneric::addExportCSVScript(); // Aggiungo script per esportazione CSV
    html += viewGeneric::addAutoRefreshControlScript(); // 🔧 FIX: Script controllo auto-refresh
    html += "<h1>History</h1>";
    
    // Aggiungo bottone export CSV
    html += "<div style='text-align: center; margin: 20px 0;'>";
    html += "<button onclick=\"exportToCSV('history_data.csv', 'history-table-combined')\" style='background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin-right: 10px;'>📥 Export History CSV</button>";
    html += "</div>";
    
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>"; // Add inline style for scrollbar
    
    // Creazione della tabella con header fisso - aggiungo ID per esportazione
    html += "<table class='history-table' id='history-table-combined' border='1'>";
    html += "<thead>";
    html += "<tr>";
    html += "<th>Type</th>";
    html += "<th>Pin/Address</th>";
    html += "<th>Value</th>";
    html += "<th>Actions</th>";
    html += "</tr>";
    html += "</thead>";
    
    // Il tbody è identificato per l'aggiornamento automatico tramite fetch
    html += "<tbody id='history-pin-content'>";
    html += viewHistory::pinoutContent(); 
    html += "</tbody>";
    
    html += "<tbody id='history-content'>";
    html += viewHistory::modbusContent(); 
    html += "</tbody>";
    html += "</table>";
    html += "</div>";

    // 🔧 FIX: Script aggiornamento automatico con controllo focus/blur integrato
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded', () => {";
    html += "  const refreshHistory = () => {";
    html += "    if (!window.AutoRefreshManager.isPaused) {";
    html += "      fetch('/getHistoryContent')";
    html += "        .then(response => response.text())";
    html += "        .then(data => {";
    html += "          document.getElementById('history-content').innerHTML = data;";
    html += "        });";
    html += "    }";
    html += "  };";
    html += "  const refreshPins = () => {";
    html += "    if (!window.AutoRefreshManager.isPaused) {";
    html += "      fetch('/getPinValuesHistory')";
    html += "        .then(response => response.text())";
    html += "        .then(data => {";
    html += "          document.getElementById('history-pin-content').innerHTML = data;";
    html += "        });";
    html += "    }";
    html += "  };";
    html += "  const interval1 = setInterval(refreshHistory, 3000);";
    html += "  const interval2 = setInterval(refreshPins, 3000);";
    html += "  window.AutoRefreshManager.addInterval(interval1);";
    html += "  window.AutoRefreshManager.addInterval(interval2);";
    html += "});";
    html += "</script>";

    html += viewGeneric::defaultFooter();

    return html;
}

String viewHistory::modbusContent()
{
    String html = "";
    
    std::vector<float> valuesVector = SystemState::getInstance()->getAllRegisterValue();
    std::vector<int> addresses = SystemState::getInstance()->getAllRegisterAddress();

    // Loop through each value in the vector in reverse order
    for (size_t i = valuesVector.size(); i > 0; i--)
    {
        size_t index = i - 1;
        html += "<tr>";
        html += "<td>Modbus</td>"; // Aggiungo colonna Type
        // Controlla se l'indirizzo è maggiore di 0 
        if (addresses[index] > 0) { 
            html += "<td>" + String(addresses[index]) + "</td>"; 
            // Display the address 
        } else { 
            html += "<td>GPIO:" + String(-addresses[index]) + "</td>"; 
            // Display the negative address as GPIO 
        }

        // Display the value with an input field for editing inside a form
        html += "<td>";
        html += "<form action='/editRegister' method='GET'>";
        html += "<input type='hidden' name='index' value='" + String(index) + "'>";
        html += "<input type='text' class='edit-input' name='value' value='" + String(valuesVector[index]) + "'>";
        html += "<input type='submit' value='Edit' class='action-link edit-link'>";
        html += "</form>";
        html += "</td>";

        // Add delete button with link
        html += "<td>";
        html += "<a href='/deleteRegister?index=" + String(index) + "' class='action-link delete-link'>Delete</a>"; // Delete link
        html += "</td>";

        html += "</tr>";
    }

    
    return html;
}

String viewHistory::pinoutContent() {
    String content = "";
    // Otteniamo tutti i numeri dei pin gestiti tramite l'interfaccia PinoutData
    std::vector<int> pinNumbers = SystemState::getInstance()->pinoutData->getPinNumbers();
    
    // Per ogni pin...
    for (size_t i = 0; i < pinNumbers.size(); i++) {
        int gpioPin = pinNumbers[i];
        // Recupera il riferimento al Pin corrispondente
        Pin &currentPin = SystemState::getInstance()->pinoutData->getPin(gpioPin);
        // Ottieni il vettore dei valori di tensione registrati per questo pin
        std::vector<float> valuesVector = currentPin.getValuesVoltage();

        // Se non sono presenti valori, stampa una riga informativa
        if (valuesVector.empty()) {
            content += "<tr>";
            content += "<td>Pin</td>"; // Aggiungo colonna Type
            content += "<td>" + String(gpioPin) + "</td>";
            content += "<td colspan='2'>Nessun valore registrato</td>";
            content += "</tr>";
        } else {
            // Cicla in ordine inverso (simile a modbusContent)
            for (size_t j = valuesVector.size(); j > 0; j--) {
                size_t index = j - 1;
                content += "<tr>";
                content += "<td>Pin</td>"; // Aggiungo colonna Type
                // Colonna 1: numero del pin (come indirizzo)
                content += "<td>" + String(gpioPin) + "</td>";
                
                // Colonna 2: form per modificare il valore
                content += "<td>";
                content += "<form action='/editPinValue' method='GET'>";
                content += "<input type='hidden' name='pin' value='" + String(gpioPin) + "'>";
                content += "<input type='hidden' name='index' value='" + String(index) + "'>";
                content += "<input type='text' class='edit-input' name='value' value='" + String(valuesVector[index]) + "'>";
                content += "<input type='submit' value='Edit' class='action-link edit-link'>";
                content += "</form>";
                content += "</td>";
                
                // Colonna 3: link per cancellare il valore
                content += "<td>";
                content += "<a href='/deletePinValue?pin=" + String(gpioPin) + "&index=" + String(index) + "' class='action-link delete-link'>Delete</a>";
                content += "</td>";
                
                content += "</tr>";
            }
        }
    }
    return content;
}
