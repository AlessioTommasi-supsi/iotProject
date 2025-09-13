#include "viewADS.h"

String viewADS::html = "";

String viewADS::generateHTML()
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

    html += "<h1>ADS1115 History</h1>";
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>";
    
    // Creazione della tabella con header fisso
    html += "<table class='history-table' border='1'>";
    html += "<thead>";
    html += "<tr>";
    html += "<th>Channel</th>";
    html += "<th>Signal Type</th>";
    html += "<th>Value</th>";
    html += "<th>Status</th>";
    html += "</tr>";
    html += "</thead>";
    
    // Il tbody è identificato per l'aggiornamento automatico tramite fetch
    html += "<tbody id='ads-content'>";
    html += viewADS::adsContent(); 
    html += "</tbody>";
    html += "</table>";

    html += "</div>";

    // Aggiungi lo script per aggiornare il div ogni 3 secondi
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded', () => {";
    html += "  setInterval(() => {";
    html += "    fetch('/getADSContent')";
    html += "      .then(response => response.text())";
    html += "      .then(data => {";
    html += "        document.getElementById('ads-content').innerHTML = data;";
    html += "      });";
    html += "  }, 3000);"; // Aggiorna ogni 3 secondi
    html += "});";
    html += "</script>";

    html += viewGeneric::defaultFooter();

    return html;
}

String viewADS::adsContent()
{
    String content = "";
    ADS1115_controller* adsCtrl = ADS1115_controller::getInstance();
    
    // Verifica se l'ADS è inizializzato correttamente
    if (adsCtrl->isInitializationFailed()) {
        content += "<tr>";
        content += "<td colspan='4'>ADS1115 Initialization Failed</td>";
        content += "</tr>";
        return content;
    }
    
    // Ottieni i valori registrati
    const std::vector<float>& values = adsCtrl->getRecordedValues();
    int currentChannel = adsCtrl->getCurrentChannel();
    
    // Converti il canale in signal type per la visualizzazione
    String signalType = "";
    switch(currentChannel) {
        case 0: signalType = "Resistenza CN2 [Ohm]"; break;
        case 1: signalType = "Corrente CN2 [mA]"; break;
        case 2: signalType = "ADS RAW Voltage CH=2"; break;
        case 3: signalType = "Tensione CN2 [μV]"; break;
        case 4: signalType = "Resistenza CN10 [Ohm]"; break;
        case 5: signalType = "Corrente CN10 [mA]"; break;
        case 6: signalType = "ADS RAW Voltage CH=6"; break;
        case 7: signalType = "Tensione CN10 [μV]"; break;
        case 8: signalType = "Termocoppia K CN2"; break;
        case 9: signalType = "PT100 CN2"; break;
        case 10: signalType = "Termocoppia K CN10"; break;
        case 11: signalType = "PT100 CN10"; break;
        case 12: signalType = "PT1000 CN2"; break;
        case 13: signalType = "PT1000 CN10"; break;
        default: signalType = "Unknown"; break;
    }
    
    if (values.empty()) {
        content += "<tr>";
        content += "<td>" + String(currentChannel) + "</td>";
        content += "<td>" + signalType + "</td>";
        content += "<td>No recordings</td>";
        content += "<td>Idle</td>";
        content += "</tr>";
    } else {
        // Mostra gli ultimi 10 valori in ordine inverso (più recenti prima)
        int startIndex = values.size() > 10 ? values.size() - 10 : 0;
        for (size_t i = values.size(); i > startIndex; i--) {
            size_t index = i - 1;
            content += "<tr>";
            content += "<td>" + String(currentChannel) + "</td>";
            content += "<td>" + signalType + "</td>";
            content += "<td>" + String(values[index], 4) + "</td>";
            content += "<td>" + String(index == values.size() - 1 ? "Latest" : "Historical") + "</td>";
            content += "</tr>";
        }
    }
    
    return content;
}