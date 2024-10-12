#include "viewConfig.h"

String viewConfig::html = "";

String viewConfig::generateListComponents( std::vector<std::string> &networks)
{
    String html = "<div class='form-container'>";
    html += "<form action='/switch_wifi' method='get'>";
    html += "<label for='network'>Select Network:</label>";
    html += "<select id='ssid' name='ssid' required>";

    for (const std::string &network : networks)
    {
        html += "<option value='" + String(network.c_str()) + "'>" + String(network.c_str()) + "</option>";
    }

    html += "</select>";
    html += "<label for='password'>Password:</label>";
    html += "<input type='password' id='password' name='password' required>";
    html += "<button type='submit'>Connect</button>";
    html += "</form>";
    html += "</div>";

    return html;
}

String viewConfig::generateHTML(std::vector<std::string> ssidList)
{
    String html = viewGeneric::defaultCssHeader("Config Page");

    html += viewConfig::generateListComponents(ssidList);

    html += viewGeneric::defaultFooter();

    return html;
}

String viewConfig::generateHTML() 
{
    html = "Config Page";

    return html;
}