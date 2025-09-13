#include "pinout.h"
#include "viewGraph.h"

String Pinout::html = "";

String Pinout::generateHTML()
{
    // Header ultra-minimalista
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Pinout</title>";
    html += "<style>";
    html += "body{margin:0;padding:60px 10px 120px;background:#f4f4f4}";
    // CSS per popup
    html += ".popup{position:fixed;top:20px;right:20px;background:#4CAF50;color:white;padding:15px;border-radius:5px;z-index:1000;box-shadow:0 4px 8px rgba(0,0,0,0.2)}";
    html += ".popup.error{background:#f44336}";
    html += "</style>";
    html += "</head><body>";
    
    // Prima carico tutto il sistema dinamico originale
    html += viewGeneric::dynamicUpdateContentScript();
    html += viewGeneric::dynamicUpdateContent("navbar_area", "/navbarStyle", -1);
    html += viewGeneric::dynamicUpdateContent("pinout_content", "/pinoutPageContent", -1);
    
    html += "<div id='navbar_area'></div>";
    html += viewGeneric::addNavbar();
    html += "<div id='pinout_content'><div style='text-align:center;padding:20px'>Loading pins...</div></div>";
    
    html += "</body></html>";
    return html;
}

String Pinout::pageContent()
{
    // CSS minimalista inline
    html = "<style>";
    html += ".pin-container{background:rgba(255,255,255,0.9);border-radius:8px;padding:15px;margin:10px auto;width:90%;max-width:500px}";
    html += ".pin-info{margin-bottom:8px;font-weight:bold;font-size:14px}";
    html += ".pin-actions{margin-top:10px}.pin-actions button{padding:6px 10px;border:none;border-radius:4px;margin-right:6px;font-size:12px;cursor:pointer}";
    html += ".start{background:#4CAF50;color:white}.stop{background:#f44336;color:white}.edit{background:#2196F3;color:white}";
    html += ".popup{position:fixed;top:20px;right:20px;background:#4CAF50;color:white;padding:15px;border-radius:5px;z-index:1000;box-shadow:0 4px 8px rgba(0,0,0,0.2)}";
    html += ".popup.error{background:#f44336}";
    html += "</style>";

    html += "<h1 style='text-align:center;margin:20px 0'>🔌 Pinout Configuration</h1>";

    // Genera pin dinamicamente per evitare heap overflow
    std::vector<int> pinNumbers = SystemState::getInstance()->pinoutData->getPinNumbers();
    
    for (int pinNumber : pinNumbers) 
    {
        Pin currentPin = SystemState::getInstance()->pinoutData->getPin(pinNumber);
        
        html += "<div class='pin-container'>";
        html += "<div class='pin-info'>";
        char noteBuffer[200];
        currentPin.getNote(noteBuffer, sizeof(noteBuffer));
        html += "Pin number: " + String(pinNumber) + ", Type: " + currentPin.getType() + ", Voltage: " + String(currentPin.getVoltage() / 1000.0, 3) + " V, Input: " + (currentPin.getIsInput() ? "Yes" : "No") + ", Note: " + String(noteBuffer);
        html += "</div>";
        
        html += "<div class='pin-actions'>";
        
        // Form per start recording (solo per pin input) - RIPRISTINATO con action originale
        if (currentPin.getIsInput()) {
            html += "<form action='/startRecordingPin' method='get' class='start-form' data-pin='" + String(pinNumber) + "' style='display:inline-block;margin-right:5px'>";
            html += "<input type='hidden' name='pin' value='" + String(pinNumber) + "'>";
            html += "<label for='milliseconds'>ms:</label>";
            html += "<input type='text' name='milliseconds' value='1000' style='width:60px;margin-right:5px'>";
            html += "<button type='submit' class='start'>Start Recording</button>";
            html += "</form>";
            
            html += "<form action='/stopRecordingPin' method='get' class='stop-form' data-pin='" + String(pinNumber) + "' style='display:inline-block;margin-right:5px'>";
            html += "<input type='hidden' name='pin' value='" + String(pinNumber) + "'>";
            html += "<button type='submit' class='stop'>Stop Recording</button>";
            html += "</form>";
        }
        
        // Form per edit (sempre presente)
        html += "<form action='/editPin' method='get' style='display:inline-block'>";
        html += "<input type='hidden' name='pin' value='" + String(pinNumber) + "'>";
        html += "<button type='submit' class='edit'>Edit</button>";
        html += "</form>";
        
        html += "</div></div>";
    }

    // JavaScript per gestire i form AJAX e i popup
    html += "<script>";
    html += "function showPopup(message, isError = false) {";
    html += "  const popup = document.createElement('div');";
    html += "  popup.className = 'popup' + (isError ? ' error' : '');";
    html += "  popup.textContent = message;";
    html += "  document.body.appendChild(popup);";
    html += "  setTimeout(() => popup.remove(), 4000);";
    html += "}";
    
    html += "document.addEventListener('DOMContentLoaded', function() {";
    html += "  // Gestione form start recording";
    html += "  document.querySelectorAll('.start-form').forEach(form => {";
    html += "    form.addEventListener('submit', function(e) {";
    html += "      e.preventDefault();";
    html += "      const formData = new FormData(this);";
    html += "      const params = new URLSearchParams(formData);";
    html += "      fetch('/startRecordingPin?' + params.toString())";
    html += "        .then(response => response.json())";
    html += "        .then(data => {";
    html += "          if (data.success) {";
    html += "            showPopup(data.message);";
    html += "          } else {";
    html += "            showPopup(data.message, true);";
    html += "          }";
    html += "        })";
    html += "        .catch(error => showPopup('Errore di rete durante avvio registrazione', true));";
    html += "    });";
    html += "  });";
    
    html += "  // Gestione form stop recording";
    html += "  document.querySelectorAll('.stop-form').forEach(form => {";
    html += "    form.addEventListener('submit', function(e) {";
    html += "      e.preventDefault();";
    html += "      const formData = new FormData(this);";
    html += "      const params = new URLSearchParams(formData);";
    html += "      fetch('/stopRecordingPin?' + params.toString())";
    html += "        .then(response => response.json())";
    html += "        .then(data => {";
    html += "          if (data.success) {";
    html += "            showPopup(data.message);";
    html += "          } else {";
    html += "            showPopup(data.message, true);";
    html += "          }";
    html += "        })";
    html += "        .catch(error => showPopup('Errore di rete durante stop registrazione', true));";
    html += "    });";
    html += "  });";
    html += "});";
    html += "</script>";

    // JavaScript minimalista per refresh periodico
    html += "<script>setTimeout(()=>{if(typeof loadPageContent==='function')loadPageContent('/pinoutPageContent','pinout_content',-1)},30000)</script>";
    
    return html;
}

String Pinout::pageContentCss(){
    String css ="";

    css += viewGeneric::dynamicUpdateContentScript(); //aggiungo script per aggiornamento dinamico

    /**
     * Aggiungo Css effettivo
     */

    css += viewGeneric::dynamicUpdateContent("", "/formStyle", -1); //aggiungo script per aggiornamento dinamico
    css += viewGeneric::dynamicUpdateContent("", "/pinStyle", -1); //aggiungo script per aggiornamento dinamico
    css += viewGeneric::dynamicUpdateContent("", "/navbarStyle", -1); //aggiungo script per aggiornamento dinamico

    return css;
}


String Pinout::generateHTML(String popupScript)
{
    // Header completo con CSS e navbar
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Pinout</title>";
    html += "<style>";
    html += viewGeneric::addCss();
    html += viewGeneric::addFormCss();
    html += viewGeneric::addNavbarCss();
    html += "</style>";
    html += "</head><body>";
    
    // Navbar sempre presente
    html += viewGeneric::addNavbar();

    // Contenuto della pagina
    html += pageContent();

    // Popup
    html += "<div id='popup' style='display:none; position:fixed; top:50%; left:50%; transform:translate(-50%, -50%); padding:20px; background-color:white; border:1px solid black; z-index:1000;'>";
    html += "    <p id='popupMessage'></p>";
    html += "    <button onclick=\"document.getElementById('popup').style.display='none';\">Close</button>";
    html += "</div>";

    // JavaScript per popup
    html += "<script>";
    html += "function showPopup(message) {";
    html += "    document.getElementById('popupMessage').innerText = message;";
    html += "    document.getElementById('popup').style.display = 'block';";
    html += "}";
    html += "</script>";

    // Script personalizzato se fornito
    if (popupScript != "")
    {
        html += "<script>";
        html += popupScript;
        html += "</script>";
    }

    html += viewGeneric::defaultFooter();

    return html;
}

String Pinout::generateHTMLWithPopup(String popupType, String popupMessage)
{
    // Header ultra-minimalista
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Pinout</title>";
    html += "<style>";
    html += "body{margin:0;padding:60px 10px 120px;background:#f4f4f4}";
    // CSS per popup
    html += ".popup{position:fixed;top:20px;right:20px;background:#4CAF50;color:white;padding:15px;border-radius:5px;z-index:1000;box-shadow:0 4px 8px rgba(0,0,0,0.2);display:none}";
    html += ".popup.error{background:#f44336}";
    html += ".popup.success{background:#4CAF50}";
    html += "</style>";
    html += "</head><body>";
    
    // Prima carico tutto il sistema dinamico originale
    html += viewGeneric::dynamicUpdateContentScript();
    html += viewGeneric::dynamicUpdateContent("navbar_area", "/navbarStyle", -1);
    html += viewGeneric::dynamicUpdateContent("pinout_content", "/pinoutPageContent", -1);
    
    html += "<div id='navbar_area'></div>";
    html += viewGeneric::addNavbar();
    html += "<div id='pinout_content'><div style='text-align:center;padding:20px'>Loading pins...</div></div>";
    
    // Popup con messaggio
    html += "<div id='popup' class='popup " + popupType + "'>" + popupMessage + "</div>";
    
    // JavaScript per mostrare il popup
    html += "<script>";
    html += "document.addEventListener('DOMContentLoaded', function() {";
    html += "  const popup = document.getElementById('popup');";
    html += "  if (popup) {";
    html += "    popup.style.display = 'block';";
    html += "    setTimeout(() => {";
    html += "      popup.style.display = 'none';";
    html += "    }, 4000);";
    html += "  }";
    html += "});";
    html += "</script>";
    
    html += "</body></html>";
    return html;
}