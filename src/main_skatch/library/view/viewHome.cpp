#include "viewHome.h"
#include "viewGraph.h"

String viewHome::html = "";

String viewHome::generateHTML()
{
    // Header minimalista senza CSS esterni
    html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'>";
    html += "<title>ALPHA</title>";
    html += "<style>body{margin:0;padding:0;background:#f4f4f4}</style>";
    html += "</head><body>";
    
    // Carica tutto dinamicamente per ridurre heap iniziale
    html += viewGeneric::dynamicUpdateContentScript();
    html += viewGeneric::dynamicUpdateContent("main_content", "/homePageContent", -1);
    html += "<div id='main_content'><div style='text-align:center;padding:50px'> </div></div>";
    
    html += "</body></html>";
    return html;
}

String viewHome::pageContent()
{
    html = "";
    
    // CSS inline ottimizzato per homepage
    html += "<style>";
    html += "body{font:14px Arial;margin:0;padding:50px 10px 120px;background:#f4f4f4}";
    html += ".project_maxwidth{max-width:600px;margin:0 auto;background:rgba(255,255,255,0.95);border-radius:15px;padding:30px;box-shadow:0 4px 8px rgba(0,0,0,0.1)}";
    html += ".knowledge-button{background:#4CAF50;color:white;border:none;padding:8px 12px;margin:3px;border-radius:20px;font-size:12px;cursor:pointer}";
    html += ".download-button{background:#2196F3;color:white;border:none;padding:10px 15px;margin:5px;border-radius:5px;text-decoration:none;display:inline-block;font-size:14px}";
    html += ".download-button:hover{background:#1976D2}";
    html += "#GetInTouchBtn,#ResumeBtn{position:fixed;bottom:80px;width:50px;height:50px;border-radius:50%;border:none;font-size:20px;cursor:pointer;box-shadow:0 4px 8px rgba(0,0,0,0.2)}";
    html += "#GetInTouchBtn{right:80px;background:#4CAF50;color:white}";
    html += "#ResumeBtn{right:20px;background:#FF9800;color:white}";
    html += viewGeneric::addNavbarCss(); // Navbar CSS
    html += "</style>";
    
    // Navbar sempre presente
    html += viewGeneric::addNavbar();
    
    // Contenuto ALPHA come richiesto
    html += "<div class='project_maxwidth responsive_text'>";
    html += "<h3>ALPHA</h3>";
    html += "<p>";
    html += "<button class='knowledge-button'>C++</button>";
    html += "<button class='knowledge-button'>ESP32</button>";
    html += "<button class='knowledge-button'>MODBUS</button>";
    html += "<button class='knowledge-button'>CSS</button>";
    html += "</p>";
    html += "<p>Acquisizione Locale di Parametri con Hardware Avanzato</p>";
    html += "<p>Il progetto ALPHA è stato sviluppato nel corso di IoT del Master in Informatica presso SUPSI. Il focus principale è sull'ESP32 e il protocollo Modbus</p>";
    
    // Link ufficiali
    html += "<a href='https://github.com/AlessioTommasi-supsi/iotProject/blob/main/docs/tesi.pdf'>";
    html += "<button class='download-button'>official</button></a>";
    html += "<a href='https://github.com/AlessioTommasi-supsi/iotProject/tree/main/docs'>";
    html += "<button class='download-button'>github docs</button></a>";
    html += "<a href='https://github.com/AlessioTommasi-supsi/iotProject/tree/main'>";
    html += "<button class='download-button'>official repo</button></a>";
    html += "</div>";
    
    // Bottoni di contatto fissi
    html += "<a href='mailto:alessio.tommasi.lavoro@gmail.com'><button id='GetInTouchBtn'>📲</button></a>";
    html += "<a href='http://alessiotommasi.com/model/docs/curriculum.pdf'><button id='ResumeBtn'>📖</button></a>";
    
    return html;
}
