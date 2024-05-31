#include "viewHistory.h"

String viewHistory::html = "";

String viewHistory::generateHTML()
{
    html = viewGeneric::defaultCssHeader("History Register");

    html += "<h1>History Register</h1>";
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>"; // Aggiunto stile inline per la scrollbar
    html += "<table class='history-table'>";
    html += "<tr>";
    html += "<th>Address</th>";
    html += "<th>Value</th>";
    html += "</tr>";

    std::vector<float> valuesVector = SystemState::getInstance()->getAllRegisterValue();
    int prec_register = -1;

    for (int i = 0; i < SystemState::getInstance()->getAllRegisterAddress().size(); i++)
    {
        html += "<tr>";
        html += "<td>";
        if (prec_register != SystemState::getInstance()->getAllRegisterAddress()[i])
        {
            html += String(SystemState::getInstance()->getAllRegisterAddress()[i]);
            prec_register = SystemState::getInstance()->getAllRegisterAddress()[i];
        }
        html += "</td>";
        html += "<td>";
        html += String(valuesVector[i]);
        html += "</td>";
        html += "</tr>";
    }

    html += "</table>";
    html += "</div>";
    html += viewGeneric::defaultFooter();

    return html;
}
