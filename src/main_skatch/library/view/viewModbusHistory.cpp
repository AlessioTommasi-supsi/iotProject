#include "viewModbusHistory.h"

String viewModbusHistory::html = "";

String viewModbusHistory::generateHTML()
{
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Modbus History</title>";
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
    html += "<h1>Modbus History</h1>";
    
    // Aggiungo bottone export CSV
    html += "<div style='text-align: center; margin: 20px 0;'>";
    html += "<button onclick=\"exportToCSV('modbus_history_data.csv', 'modbus-history-table')\" style='background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin-right: 10px;'>📥 Export Modbus CSV</button>";
    html += "</div>";
    
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>";
    html += "<table class='history-table' id='modbus-history-table' border='1'>";
    html += "<thead>";
    html += "<tr>";
    html += "<th>Address</th>";
    html += "<th>Value</th>";
    html += "<th>Actions</th>";
    html += "</tr>";
    html += "</thead>";
    
    html += "<tbody id='modbus-history-content'>";
    html += viewModbusHistory::modbusContent(); 
    html += "</tbody>";
    html += "</table>";
    html += "</div>";

    // 🔧 FIX: Script aggiornamento automatico con controllo focus/blur integrato
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded', () => {";
    html += "  const refreshModbusHistory = () => {";
    html += "    if (!window.AutoRefreshManager.isPaused) {";
    html += "      fetch('/getModbusValuesHistory')";
    html += "        .then(response => response.text())";
    html += "        .then(data => {";
    html += "          document.getElementById('modbus-history-content').innerHTML = data;";
    html += "        });";
    html += "    }";
    html += "  };";
    html += "  const interval = setInterval(refreshModbusHistory, 3000);";
    html += "  window.AutoRefreshManager.addInterval(interval);";
    html += "});";
    html += "</script>";

    html += viewGeneric::defaultFooter();

    return html;
}

String viewModbusHistory::modbusContent()
{
    String content = "";
    
    std::vector<float> valuesVector = SystemState::getInstance()->getAllRegisterValue();
    std::vector<int> addresses = SystemState::getInstance()->getAllRegisterAddress();

    for (size_t i = valuesVector.size(); i > 0; i--)
    {
        size_t index = i - 1;
        content += "<tr>";
        
        // Solo registri Modbus (indirizzi positivi)
        if (addresses[index] > 0) { 
            content += "<td>" + String(addresses[index]) + "</td>"; 
            
            content += "<td>";
            content += "<form action='/editRegister' method='GET'>";
            content += "<input type='hidden' name='index' value='" + String(index) + "'>";
            content += "<input type='text' class='edit-input' name='value' value='" + String(valuesVector[index]) + "'>";
            content += "<input type='submit' value='Edit' class='action-link edit-link'>";
            content += "</form>";
            content += "</td>";

            content += "<td>";
            content += "<a href='/deleteRegister?index=" + String(index) + "' class='action-link delete-link'>Delete</a>";
            content += "</td>";

            content += "</tr>";
        }
        // Esclude completamente i pin (indirizzi negativi)
    }

    if (content.length() == 0) {
        content += "<tr><td colspan='3'>No Modbus register values recorded</td></tr>";
    }
    
    return content;
}