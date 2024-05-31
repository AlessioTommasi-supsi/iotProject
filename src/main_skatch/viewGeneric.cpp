#include "viewGeneric.h"

String viewGeneric::html = "";

String viewGeneric::addCss()
{
    String css = "body {";
    css += "font-family: Arial, sans-serif;";
    css += "background-color: #f2f2f2;";
    css += "display: flex;";
    css += "flex-direction: column;";
    css += "justify-content: center;";
    css += "align-items: center;";
    css += "height: 100vh;";
    css += "margin: 0;";
    css += "}";
    css += ".navbar {";
    css += "display: flex;";
    css += "justify-content: center;";
    css += "background-color: #333;";
    css += "width: 100%;";
    css += "padding: 10px 0;";
    css += "position: fixed;";
    css += "top: 0;";
    css += "}";
    css += ".navbar a {";
    css += "color: white;";
    css += "padding: 14px 20px;";
    css += "text-align: center;";
    css += "text-decoration: none;";
    css += "font-size: 17px;";
    css += "}";
    css += ".navbar a:hover {";
    css += "background-color: #ddd;";
    css += "color: black;";
    css += "}";
    css += ".form-container {";
    css += "background-color: white;";
    css += "padding: 20px;";
    css += "border-radius: 8px;";
    css += "box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);";
    css += "margin-top: 60px;";
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
    css += ".history-table {";
    css += "width: 80%;";
    css += "border-collapse: collapse;";
    css += "margin: 20px 0;";
    css += "font-size: 18px;";
    css += "text-align: left;";
    css += "}";
    css += ".history-table th, .history-table td {";
    css += "padding: 12px 15px;";
    css += "border: 1px solid #ddd;";
    css += "}";
    css += ".history-table th {";
    css += "background-color: #f2f2f2;";
    css += "}";
    css += ".history-table tr:nth-child(even) {";
    css += "background-color: #f9f9f9;";
    css += "}";
    css += ".history-table tr:nth-child(odd) {";
    css += "background-color: #fff;";
    css += "}";
    return css;
}

String viewGeneric::addNavbar()
{
    String navbar = "<div class='navbar'>";
    navbar += "<a href='/currentregister'>Current Register</a>";
    navbar += "<a href='/history'>History</a>";
    navbar += "<a href='/graph'>Graph</a>";
    navbar += "<a href='/config'>Config</a>";
    navbar += "</div>";
    return navbar;
}

String viewGeneric::defaultHeader()
{
    html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    // html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>DefaultTitle</title>";
    html += "</head>";
    html += "<body>";
    html += addNavbar();
    return html;
}

String viewGeneric::defaultCssHeader(String title)
{
    html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    // html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>";
    html += title;
    html += "</title>";
    html += "<style>";
    html += addCss();
    html += "</style>";
    html += "</head>";
    html += "<body>";
    html += addNavbar();
    return html;
}

String viewGeneric::defaultHeader(String title)
{
    html = "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    // html += "<meta http-equiv='refresh' content='5'>";//refresh automatico della pagina ogni 5 sec indesiderato!
    html += "<title>";
    html += title;
    html += "</title>";
    html += "</head>";
    html += "<body>";
    html += addNavbar();
    return html;
}

String viewGeneric::defaultFooter()
{
    html = "</body>";
    html += "</html>";
    return html;
}