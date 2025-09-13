#include "viewCurrentRegister.h"

String viewCurrentRegister::html = "";

String viewCurrentRegister::generateEmptyFormRegister()
{
    int registerAddress = 0;
    float registerValue = 0.0;
    String form ;

    form += "<div class=\"form-container\">";
    form += "    <form action=\"modbusMaster\" method=\"get\">";
    form += "        <label for=\"registerAddress\">Register Address:</label>";
    form += "        <input type=\"text\" id=\"registerAddress\" name=\"registerAddress\" required>";
    form += "        <label for=\"registerType\">Register Type:</label>";
    form += "        <select id=\"registerType\" name=\"registerType\" required>";
    form += "            <option value=\"int\">int</option>";
    form += "            <option value=\"float\">float</option>";
    form += "        </select>";
    form += "        <button type=\"submit\">Monitor as Master</button>";
    form += "    </form>";
    form += "</div>";

    form += "<br><br><br>";

    form += "<div class=\"form-container\">";
    form += "    <form action=\"modbusSlave\" method=\"get\">";
    form += "        <label for=\"registerAddress\">Register Address:</label>";
    form += "        <input type=\"text\" id=\"registerAddress\" name=\"registerAddress\" value=\"" + String(registerAddress) + "\" required>";
    form += "        <label for=\"registerAddress\">Register Value:</label>";
    form += "        <input type=\"text\" id=\"registerAddress\" name=\"registerValue\" value=\"" + String(registerValue) + "\" required>";
    form += "        <label for=\"registerType\">Register Type:</label>";
    form += "        <select id=\"registerType\" name=\"registerType\" required>";
    form += "            <option value=\"int\">int</option>";
    form += "            <option value=\"float\">float</option>";
    form += "        </select>";\
    form += "        <button type=\"submit\">Write As Slave</button>";
    form += "    </form>";
    form += "</div>";

    return form;
}


String viewCurrentRegister::generateHTML(String popupScript) //codice generato solo la prima volta quando nessun registro e stato ancora selezionato!
{
    html = viewGeneric::defaultCssHeader("Current Register");

    html += viewCurrentRegister::generateEmptyFormRegister();

    if (popupScript.length() > 0) {
        html += "<div id='popupOverlay' style='display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.5);z-index:999' onclick=\"document.getElementById('popup').style.display='none';document.getElementById('popupOverlay').style.display='none'\"></div>";
        html += "<div id='popup' style='display:none;position:fixed;top:50%;left:50%;transform:translate(-50%,-50%);padding:15px;background:white;border:1px solid #ccc;border-radius:8px;z-index:1000;box-shadow:0 4px 8px rgba(0,0,0,0.2)'>";
        html += "<p id='popupMessage'></p>";
        html += "<button onclick=\"document.getElementById('popup').style.display='none';document.getElementById('popupOverlay').style.display='none'\" style='background:#4CAF50;color:white;border:none;padding:8px 12px;border-radius:4px;cursor:pointer'>Close</button>";
        html += "</div>";
        html += "<script>function showPopup(m){document.getElementById('popupMessage').innerText=m;document.getElementById('popup').style.display='block';document.getElementById('popupOverlay').style.display='block'}</script>";
        html += "<script>" + popupScript + "</script>";
    }

    html += viewGeneric::defaultFooter();

    return html;
}

String viewCurrentRegister::generateMasterHtml(String registerAddress, float registerValue)
{
    return viewCurrentRegister::generateMasterHtml(registerAddress, registerValue, "");
}

String viewCurrentRegister::generateMasterHtml(String registerAddress, float registerValue, String popupScript = "")
{
    // Header ultra-minimalista con caricamento dinamico totale
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>Current Register</title>";
    html += "<style>body{margin:0;padding:60px 10px 120px;background:#f4f4f4}</style>";
    html += "</head><body>";
    
    // Tutto frammentato dinamicamente
    html += viewGeneric::dynamicUpdateContentScript();
    html += viewGeneric::dynamicUpdateContent("navbar_area", "/navbarStyle", -1);
    html += viewGeneric::dynamicUpdateContent("register_content", "/currentRegisterPageContent?registerAddress=" + registerAddress + "&registerValue=" + String(registerValue), -1);
    
    html += "<div id='navbar_area'></div>";
    html += viewGeneric::addNavbar();
    html += "<div id='register_content'><div style='text-align:center;padding:20px'>Loading register...</div></div>";
    
    // Popup minimale
    html += "<div id='popupOverlay' style='display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.5);z-index:999' onclick=\"document.getElementById('popup').style.display='none';document.getElementById('popupOverlay').style.display='none'\"></div>";
    html += "<div id='popup' style='display:none;position:fixed;top:50%;left:50%;transform:translate(-50%,-50%);padding:15px;background:white;border:1px solid #ccc;border-radius:8px;z-index:1000;box-shadow:0 4px 8px rgba(0,0,0,0.2)'>";
    html += "<p id='popupMessage'></p>";
    html += "<button onclick=\"document.getElementById('popup').style.display='none';document.getElementById('popupOverlay').style.display='none'\" style='background:#4CAF50;color:white;border:none;padding:8px 12px;border-radius:4px;cursor:pointer'>Close</button>";
    html += "</div>";
    
    // Script popup compresso
    html += "<script>function showPopup(m){document.getElementById('popupMessage').innerText=m;document.getElementById('popup').style.display='block';document.getElementById('popupOverlay').style.display='block'}</script>";
    
    // Script personalizzato se fornito
    if (popupScript.length() > 0) {
        html += "<script>" + popupScript + "</script>";
    }
    
    html += "</body></html>";
    return html;
}

String viewCurrentRegister::pageContent(String registerAddress, float registerValue)
{
    html = "";
    
    // CSS inline super compresso
    html += "<style>";
    html += ".form-container{background:rgba(255,255,255,0.95);border-radius:10px;padding:20px;margin:20px auto;max-width:500px}";
    html += "form{display:flex;flex-direction:column}label{font-weight:bold;margin-bottom:5px;font-size:14px}";
    html += "input,select{margin-bottom:10px;padding:8px;border:1px solid #ccc;border-radius:4px;font-size:14px}";
    html += "button{padding:10px;background:#4CAF50;color:white;border:none;border-radius:4px;cursor:pointer;font-size:14px;margin:5px 0}";
    html += "button:hover{background:#45a049}.action-btn{display:inline-block;margin:5px;padding:8px 12px;text-decoration:none;border-radius:4px;font-size:12px}";
    html += ".start{background:#4CAF50;color:white}.stop{background:#f44336;color:white}.master{background:#2196F3;color:white}";
    html += "</style>";
    
    html += "<h1 style='text-align:center;margin:20px 0'>📋 Current Register</h1>";
    
    // Form principale compatto
    html += "<div class='form-container'>";
    html += "<form action='/modbusMaster' method='get'>";
    html += "<label>Register Address:</label>";
    html += "<input type='number' name='registerAddress' value='" + registerAddress + "' required>";
    html += "<label>Register Type:</label>";
    html += "<select name='registerType' required>";
    html += "<option value='int'>Integer</option>";
    html += "<option value='float'>Float</option>";
    html += "</select>";
    html += "<button type='submit'>🔍 Read Master</button>";
    html += "</form></div>";
    
    // Mostra valore attuale se presente
    if (registerAddress.length() > 0) {
        html += "<div class='form-container'>";
        html += "<h3>Current Value: " + String(registerValue) + "</h3>";
        html += "<p>Address: " + registerAddress + "</p>";
        
        // Azioni rapide
        html += "<div style='text-align:center;margin:15px 0'>";
        html += "<a href='/storevalue?registerAddress=" + registerAddress + "&registerValue=" + String(registerValue) + "' class='action-btn start'>💾 Store</a>";
        html += "<a href='/startRecording?registerAddress=" + registerAddress + "&milliseconds=1000' class='action-btn master'>▶ Record</a>";
        html += "<a href='/stopRecording?registerAddress=" + registerAddress + "' class='action-btn stop'>⏹ Stop</a>";
        html += "</div>";
        
        // Form slave compatto
        html += "<form action='/modbusSlave' method='get' style='margin-top:15px'>";
        html += "<input type='hidden' name='registerAddress' value='" + registerAddress + "'>";
        html += "<label>Write Value:</label>";
        html += "<input type='number' name='registerValue' step='0.01' required>";
        html += "<select name='registerType' required>";
        html += "<option value='int'>Integer</option>";
        html += "<option value='float'>Float</option>";
        html += "</select>";
        html += "<button type='submit'>✍ Write Slave</button>";
        html += "</form>";
        html += "</div>";
    }
    
    return html;
}
String viewCurrentRegister::generateHTMLConfirm(String registerAddress, float registerValue)
{
    // Creazione dell'header HTML con il foglio di stile CSS
    String html = viewGeneric::defaultCssHeader(" Register Saved!");

    // Aggiunta del contenitore principale per il messaggio di conferma
    html += "<div class=\"container\">";

    // Creazione del messaggio di conferma
    html += "<div style=\"text-align: center; margin-top: 20px;\">";
    html += "    <h2>Register Value " + String(registerValue) + " stored at address " + registerAddress + "</h2>";
    html += "</div>";

    // Chiusura del contenitore principale
    html += "</div>";

    html += viewCurrentRegister::generateEmptyFormRegister();

    // Aggiunta del footer
    html += viewGeneric::defaultFooter();

    return html;
}
String viewCurrentRegister::generateOfflineHTML(String registerAddress, float registerValue, String popupScript)
{
    // Header completamente locale senza risorse esterne
    String html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    html += "<meta charset=\"UTF-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<title>Current Register</title>";
    html += "<style>";
    html += viewGeneric::addCss();
    html += viewGeneric::addFormCss();
    html += viewGeneric::addNavbarCss();
    html += "</style>";
    html += "</head>";
    html += "<body>";
    
    // Navbar locale
    html += viewGeneric::addNavbar();
    
    // Contenuto della pagina
    html += pageContent(registerAddress, registerValue);
    
    // Script per popup senza dipendenze esterne
    html += "<script>";
    html += "function showPopup(message) {";
    html += "  document.getElementById('popupMessage').innerText = message;";
    html += "  document.getElementById('popup').style.display = 'block';";
    html += "  document.getElementById('popupOverlay').style.display = 'block';";
    html += "}";
    html += "</script>";
    
    // Esecuzione del popup se presente
    if (popupScript != "") {
        html += "<script>";
        html += "window.addEventListener('DOMContentLoaded', function() {";
        html += popupScript;
        html += "});";
    }
    
    html += "</body>";
    html += "</html>";
    
    return html;
}

String viewCurrentRegister::generateHtmlSlave()
{
    String html = viewGeneric::defaultCssHeader("Slave Success");

    // Include form CSS for styling
    html += "<style>";
    html += viewGeneric::addFormCss();
    html += ".btn { display: inline-block; padding: 10px 20px; background: #4CAF50; color: white; text-decoration: none; border-radius: 4px; font-size: 14px; }";
    html += ".btn:hover { background: #45a049; }";
    html += "</style>";

    html += "<div class=\"form-container\" style=\"text-align: center;\">";
    html += "<h1 style=\"color: #4CAF50;\">Scrittura avviata con successo!</h1>";
    html += "<p>Il registro è stato scritto correttamente come slave.</p>";
    html += "<a href=\"/currentregister\" class=\"btn\">OK</a>";
    html += "</div>";

    html += viewGeneric::defaultFooter();

    return html;
}
