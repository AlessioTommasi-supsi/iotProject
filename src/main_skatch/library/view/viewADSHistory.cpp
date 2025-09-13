#include "viewADSHistory.h"
#include "ADS1115_controller.h"

String viewADSHistory::html = "";

String viewADSHistory::generateHTML()
{
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>ADS History</title>";
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
    html += "<h1>ADS History</h1>";
    
    // Aggiungo bottone export CSV
    html += "<div style='text-align: center; margin: 20px 0;'>";
    html += "<button onclick=\"exportToCSV('ads_history_data.csv', 'ads-history-table')\" style='background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; margin-right: 10px;'>📥 Export ADS CSV</button>";
    html += "</div>";
    
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>";
    html += "<table class='history-table' id='ads-history-table' border='1'>";
    html += "<thead>";
    html += "<tr>";
    html += "<th>Channel</th>";
    html += "<th>Value</th>";
    html += "<th>Actions</th>";
    html += "</tr>";
    html += "</thead>";
    
    html += "<tbody id='ads-history-content'>";
    html += viewADSHistory::adsContent(); 
    html += "</tbody>";
    html += "</table>";
    html += "</div>";

    // 🔧 FIX: Script aggiornamento automatico con controllo focus/blur integrato
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded', () => {";
    html += "  const refreshADSHistory = () => {";
    html += "    if (!window.AutoRefreshManager.isPaused) {";
    html += "      fetch('/getADSValuesHistory')";
    html += "        .then(response => response.text())";
    html += "        .then(data => {";
    html += "          document.getElementById('ads-history-content').innerHTML = data;";
    html += "        });";
    html += "    }";
    html += "  };";
    html += "  const interval = setInterval(refreshADSHistory, 3000);";
    html += "  window.AutoRefreshManager.addInterval(interval);";
    html += "});";
    html += "</script>";

    html += viewGeneric::defaultFooter();

    return html;
}

String viewADSHistory::adsContent()
{
    String content = "";
    ADS1115_controller* adsCtrl = ADS1115_controller::getInstance();
    const std::vector<float>& values = adsCtrl->getRecordedValues();

    if (values.empty()) {
        content += "<tr><td colspan='3'>No recorded values</td></tr>";
    } else {
        for (size_t i = 0; i < values.size(); i++) {
            content += "<tr>";
            content += "<td>" + String(i) + "</td>";
            
            // Colonna Value con possibilità di edit (se necessario in futuro)
            content += "<td>" + String(values[i]) + "</td>";
            
            // Colonna Actions con Delete
            content += "<td>";
            content += "<a href='/deleteADSValue?index=" + String(i) + "' class='action-link delete-link' style='background:#f44336;color:white;padding:4px 8px;border-radius:3px;text-decoration:none'>Delete</a>";
            content += "</td>";
            
            content += "</tr>";
        }
    }
    
    return content;
}
