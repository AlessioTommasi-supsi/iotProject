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

String viewWifiSuccessChange::generateHTML() 
{
    html = "wifi changePage Page";

    return html;
}