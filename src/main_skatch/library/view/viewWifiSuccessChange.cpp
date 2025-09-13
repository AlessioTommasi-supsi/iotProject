#include "viewWifiSuccessChange.h"

String viewWifiSuccessChange::html = "";

String viewWifiSuccessChange::generateContent( std::string ip_address)
{
    String html = "<div class='form-container'>";
   
    html += "<label for='ip_address'>New IP Address: </label>";
    html += "<input type='text' id='ip_address' name='ip_address' value='" + String(ip_address.c_str()) + "' readonly>";
    html += "<button type='submit'>OK</button>";


    return html;
}

String viewWifiSuccessChange::generateHTML(std::string ip_address)
{
    String html = viewGeneric::defaultCssHeader("wifi change Page");

    html += viewWifiSuccessChange::generateContent(ip_address);

    html += viewGeneric::defaultFooter();

    return html;
}

String viewWifiSuccessChange::generateErrorPage(const char* ssid,std::string ip_address)
{
    String html = viewGeneric::defaultCssHeader("wifi change Page");

    html += "<div class='form-container'>";
    html += "<h1>Errore durante la connessione alla rete Wi-Fi!</h1>";
    html += "<p>Controlla le credenziali inserite e riprova.</p>";
    html += "<form action='/switch_wifi' method='get'>";
    html += "<label for='ssid'>ora esp e connesso a SSID:</label>";
    html += "<input type='text' id='ssid' name='ssid' value='" + String(ssid) + "' required>";
    html += "<input type='text' id='ip_address' name='ip_address' value='" + String(ip_address.c_str()) + "' readonly>";
    html += "</form>";
    html += "</div>";

    html += viewGeneric::defaultFooter();

    return html;
}


String viewWifiSuccessChange::generateHTML() 
{
    html = "wifi changePage Page";

    return html;
}