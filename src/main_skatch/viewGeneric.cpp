#include "viewGeneric.h"

String viewGeneric::html = "";

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
    