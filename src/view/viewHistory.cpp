#include "viewHistory.h"

String viewHistory::html = "";

String viewHistory::generateHTML()
{
    html = viewGeneric::defaultCssHeader("History Register");

    html += "<h1>History Register</h1>";
    html += "<div class='scrollable-container' style='overflow-y: auto; max-height: 80vh;'>"; // Add inline style for scrollbar
    html += "<table class='history-table'>";
    html += "<tr>";
    html += "<th>Address</th>";
    html += "<th>Value</th>";
    html += "<th>Actions</th>"; // Add Actions column header
    html += "</tr>";

    std::vector<float> valuesVector = SystemState::getInstance()->getAllRegisterValue();
    std::vector<int> addresses = SystemState::getInstance()->getAllRegisterAddress();

    // Loop through each value in the vector
    for (size_t i = 0; i < valuesVector.size(); i++)
    {
        html += "<tr>";
        html += "<td>" + String(addresses[i]) + "</td>"; // Display the address

        // Display the value with an input field for editing inside a form
        html += "<td>";
        html += "<form action='/editRegister' method='GET'>";
        html += "<input type='hidden' name='index' value='" + String(i) + "'>";
        html += "<input type='text' class='edit-input' name='value' value='" + String(valuesVector[i]) + "'>";
        html += "<input type='submit' value='Edit' class='action-link edit-link'>";
        html += "</form>";
        html += "</td>";

        // Add delete button with link
        html += "<td>";
        html += "<a href='/deleteRegister?index=" + String(i) + "' class='action-link delete-link'>Delete</a>"; // Delete link
        html += "</td>";

        html += "</tr>";
    }

    html += "</table>";
    html += "</div>";
    html += viewGeneric::defaultFooter();

    return html;
}
