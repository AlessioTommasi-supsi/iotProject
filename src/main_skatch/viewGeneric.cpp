#include "viewGeneric.h"

String viewGeneric::html = "";

String viewGeneric::addCss()
{
    String css = "body {";
    css += "font-family: Arial, sans-serif;";
    css += "background-color: #f2f2f2;";
    css += "display: flex;";
    css += "flex-direction: column;"; // Aggiunto per posizionare gli elementi uno sotto l'altro
    css += "justify-content: center;";
    css += "align-items: center;";
    css += "height: 100vh;";
    css += "margin: 0;";
    css += "}";
    css += ".form-container {";
    css += "background-color: white;";
    css += "padding: 20px;";
    css += "border-radius: 8px;";
    css += "box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);";
    css += "}";
    css += "form {";
    css += "display: flex;";
    css += "flex-direction: column;";
    css += "}";
    css += "label {";
    css += "margin-bottom: 5px;";
    css += "}";
    css += "input, select {";
    css += "margin-bottom: 15px;";
    css += "padding: 8px;";
    css += "border: 1px solid #ccc;";
    css += "border-radius: 4px;";
    css += "}";
    css += "button {";
    css += "padding: 10px;";
    css += "background-color: #4CAF50;";
    css += "color: white;";
    css += "border: none;";
    css += "border-radius: 4px;";
    css += "cursor: pointer;";
    css += "}";
    css += "button:hover {";
    css += "background-color: #45a049;";
    css += "}";
    return css;
}

String viewGeneric::defaultHeader()
{
     html= "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    //html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>DefaultTitle</title>";
    html += "</head>";
    html += "<body>";
    return html;
}

String viewGeneric::defaultCssHeader(String title)
{
     html= "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    //html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>";
    html += title;
    html += "</title>";
    html += "<style>";
    html += addCss();
    html += "</style>";

    html += "</head>";
    html += "<body>";
    return html;
}

String viewGeneric::defaultHeader(String title)
{
     html= "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    //html += "<meta http-equiv='refresh' content='5'>";//refresh automatico della pagina ogni 5 sec indesiderato!
    html += "<title>";
    html += title;
    html += "</title>";
    html += "</head>";
    html += "<body>";
    return html;
}


String viewGeneric::defaultFooter()
{
     html= "</body>";
    html += "</html>";
    return html;
}
    