#include "viewCurrentRegister.h"

String viewCurrentRegister::html = "";


String viewCurrentRegister::generateHTML()
{
    
    html = viewGeneric::defaultHeader("Current Register");

    html += "<h1>Current Register</h1>";
    html += "<table border='1'>";
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
        if (prec_register != SystemState::getInstance()->getAllRegisterAddress()[i]) //per tabella piu bella
        {
            html += SystemState::getInstance()->getAllRegisterAddress()[i];
            prec_register = SystemState::getInstance()->getAllRegisterAddress()[i];
        }
        
        html += "</td>";

        html += "<td>";
        html += valuesVector[i];
        html += "</td>";
    
        
        html += "<td>";
        html += "</td>";
        html += "</tr>";
    }
    
    html += "</table>";
    html += viewGeneric::defaultFooter();
    

    return html;
}