#include "viewPinHistory.h"

String viewPinHistory::html = "";

String viewPinHistory::generateHTML()
{
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Pin History</title>";
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
    html += "<h1>Pin History</h1>";
    
    // Aggiungo bottone export CSV
    html += "<div style='text-align: center; margin: 20px 0;'>";
    html += "<button onclick=\"exportToCSV('pin_history_data.csv', 'pin-history-table')\" style='background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin-right: 10px;'>📥 Export Pin CSV</button>";
    html += "</div>";
    
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>";
    html += "<table class='history-table' id='pin-history-table' border='1'>";
    html += "<thead>";
    html += "<tr>";
    html += "<th>Pin</th>";
    html += "<th>Value</th>";
    html += "<th>Actions</th>";
    html += "</tr>";
    html += "</thead>";
    
    html += "<tbody id='pin-history-content'>";
    html += viewPinHistory::pinContent(); 
    html += "</tbody>";
    html += "</table>";
    html += "</div>";

    // 🔧 FIX: Script aggiornamento automatico con controllo focus/blur integrato
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded', () => {";
    html += "  const refreshPinHistory = () => {";
    html += "    if (!window.AutoRefreshManager.isPaused) {";
    html += "      fetch('/getPinValuesHistory')";
    html += "        .then(response => response.text())";
    html += "        .then(data => {";
    html += "          document.getElementById('pin-history-content').innerHTML = data;";
    html += "        });";
    html += "    }";
    html += "  };";
    html += "  const interval = setInterval(refreshPinHistory, 3000);";
    html += "  window.AutoRefreshManager.addInterval(interval);";
    html += "});";
    html += "</script>";

    html += viewGeneric::defaultFooter();

    return html;
}

String viewPinHistory::pinContent() {
    String content = "";
    std::vector<int> pinNumbers = SystemState::getInstance()->pinoutData->getPinNumbers();
    
    for (size_t i = 0; i < pinNumbers.size(); i++) {
        int gpioPin = pinNumbers[i];
        Pin &currentPin = SystemState::getInstance()->pinoutData->getPin(gpioPin);
        std::vector<float> valuesVector = currentPin.getValuesVoltage();

        if (valuesVector.empty()) {
            content += "<tr>";
            content += "<td>" + String(gpioPin) + "</td>";
            content += "<td colspan='2'>No values recorded</td>";
            content += "</tr>";
        } else {
            for (size_t j = valuesVector.size(); j > 0; j--) {
                size_t index = j - 1;
                content += "<tr>";
                content += "<td>" + String(gpioPin) + "</td>";
                
                // Colonna Edit con form completo
                content += "<td>";
                content += "<form action='/editPinValue' method='GET' style='display:inline-block'>";
                content += "<input type='hidden' name='pin' value='" + String(gpioPin) + "'>";
                content += "<input type='hidden' name='index' value='" + String(index) + "'>";
                content += "<input type='text' class='edit-input' name='value' value='" + String(valuesVector[index]) + "' style='width:80px'>";
                content += "<input type='submit' value='Edit' class='action-link edit-link' style='background:#2196F3;color:white;border:none;padding:4px 8px;border-radius:3px;cursor:pointer'>";
                content += "</form>";
                content += "</td>";
                
                // Colonna Delete
                content += "<td>";
                content += "<a href='/deletePinValue?pin=" + String(gpioPin) + "&index=" + String(index) + "' class='action-link delete-link' style='background:#f44336;color:white;padding:4px 8px;border-radius:3px;text-decoration:none'>Delete</a>";
                content += "</td>";
                
                content += "</tr>";
            }
        }
    }
    
    if (content.length() == 0) {
        content += "<tr><td colspan='3'>No pin values recorded</td></tr>";
    }
    
    return content;
}