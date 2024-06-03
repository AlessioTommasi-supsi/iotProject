#include "viewGraph.h"

String viewGraph::html = "";
String viewGraph::generateHTML()
{
    html = viewGeneric::defaultCssHeader("Graph View");

    html += "<h1>Graph View</h1>";

    // Menu a tendina per selezionare l'indirizzo del registro
    html += "<label for='register-select'>Select Register Address:</label>";
    html += "<select id='register-select' onchange='updateGraph()'>";

    std::vector<int> addresses = SystemState::getInstance()->getAllRegisterAddress();
    std::set<int> uniqueAddresses(addresses.begin(), addresses.end());
    for (int addr : uniqueAddresses)
    {
        html += "<option value='" + String(addr) + "'>" + String(addr) + "</option>";
    }

    html += "</select>";

    // Contenitore per il grafico
    html += "<canvas id='myChart' width='400' height='200'></canvas>";

    // Script JavaScript per Chart.js e per gestire il grafico
    html += "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>";
    html += "<script>";
    html += "let chart;";
    html += "function updateGraph() {";
    html += "  const address = document.getElementById('register-select').value;";
    html += "  fetch('/getRegisterValues?address=' + address)";
    html += "    .then(response => response.json())";
    html += "    .then(data => {";
    html += "      const labels = data.map((_, index) => index + 1);";
    html += "      const values = data;";
    html += "      const ctx = document.getElementById('myChart').getContext('2d');";
    html += "      if (chart) chart.destroy();";
    html += "      chart = new Chart(ctx, {";
    html += "        type: 'line',";
    html += "        data: {";
    html += "          labels: labels,";
    html += "          datasets: [{";
    html += "            label: 'Register Values',";
    html += "            data: values,";
    html += "            borderColor: 'rgba(75, 192, 192, 1)',";
    html += "            borderWidth: 2";
    html += "          }]";
    html += "        },";
    html += "        options: {";
    html += "          responsive: true,";
    html += "          scales: {";
    html += "            x: {";
    html += "              display: true,";
    html += "              title: {";
    html += "                display: true,";
    html += "                text: 'Sample Index'";
    html += "              }";
    html += "            },";
    html += "            y: {";
    html += "              display: true,";
    html += "              title: {";
    html += "                display: true,";
    html += "                text: 'Value'";
    html += "              }";
    html += "            }";
    html += "          }";
    html += "        }";
    html += "      });";
    html += "    });";
    html += "}";
    html += "document.addEventListener('DOMContentLoaded', () => updateGraph());"; // Per caricare il grafico all'avvio
    html += "</script>";

    html += viewGeneric::defaultFooter();

    return html;
}