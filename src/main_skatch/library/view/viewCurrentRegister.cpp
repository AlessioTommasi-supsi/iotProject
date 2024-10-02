#include "viewCurrentRegister.h"

String viewCurrentRegister::html = "";

String viewCurrentRegister::generateEmptyFormRegister()
{
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
    form += "        <button type=\"submit\">Monitor</button>";
    form += "    </form>";
    form += "</div>";

    return form;
}


String viewCurrentRegister::generateHTML() //codice generato solo la prima volta quando nessun registro e stato ancora selezionato!
{
    html = viewGeneric::defaultCssHeader("Current Register");

    html += viewCurrentRegister::generateEmptyFormRegister();

    html += viewGeneric::defaultFooter();

    return html;
}


String viewCurrentRegister::generateHTML(String registerAddress, float registerValue)
{
    // Creazione dell'header HTML con il foglio di stile CSS
    String html = viewGeneric::defaultCssHeader("Current Register");

    // Aggiunta del contenitore principale per form e valore del registro
    html += "<div class=\"container\">";

    // Creazione del primo form per monitorare il registro
    html += "<div class=\"form-container\">";
    html += "    <form action=\"modbusMaster\" method=\"get\">";
    html += "        <label for=\"registerAddress\">Register Address:</label>";
    html += "        <input type=\"text\" id=\"registerAddress\" name=\"registerAddress\" value=\"" + registerAddress + "\" required>";
    html += "        <label for=\"registerType\">Register Type:</label>";
    html += "        <select id=\"registerType\" name=\"registerType\" required>";
    html += "            <option value=\"int\">int</option>";
    html += "            <option value=\"float\">float</option>";
    html += "        </select>";
    html += "        <button type=\"submit\">Monitor</button>";
    html += "    </form>";
    html += "</div>";

    // Aggiunta del valore del registro sotto il primo form
    html += "<div style=\"text-align: center; margin-top: 20px;\">";
    html += "    <h2>Register Value: " + String(registerValue) + "</h2>";
    html += "</div>";

    // Creazione del secondo form per memorizzare il valore del registro
    html += "<div class=\"form-container\" style=\"margin-top: 20px; text-align: center;\">";
    html += "    <form action=\"/storevalue\" method=\"get\">";
    html += "        <input type=\"hidden\" name=\"registerValue\" value=\"" + String(registerValue) + "\">"; // Campo nascosto per il valore del registro
    html += "        <input type=\"hidden\" name=\"registerAddress\" value=\"" + registerAddress + "\">";     // Campo nascosto per l'indirizzo del registro
    html += "        <button type=\"submit\" style=\"padding: 10px; background-color: #007bff; color: white; border: none; border-radius: 4px; cursor: pointer;\">Store Register Value</button>";
    html += "    </form>";
    html += "</div>";

    // Chiusura del contenitore principale
    html += "</div>";

    // Aggiunta del footer
    html += viewGeneric::defaultFooter();

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


