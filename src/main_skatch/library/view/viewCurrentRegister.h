#ifndef VIEWCURRENTREGISTER_H
#define VIEWCURRENTREGISTER_H


#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include "SystemState.h"



class viewCurrentRegister
{
private:
    
public:
    static String html ;
    static String generateHTML(String popupScript = "");
    static String generateEmptyFormRegister();
    static String generateMasterHtml(String registerAddress, float registerValue);
    static String generateHTMLConfirm(String registerAddress, float registerValue);
    static String generateMasterHtml(String registerAddress, float registerValue, String popupScript);
    static String pageContent(String registerAddress, float registerValue);
    static String generateOfflineHTML(String registerAddress, float registerValue, String popupScript = "");
    static String generateHtmlSlave();

};


#endif