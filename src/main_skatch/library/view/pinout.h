#ifndef pinout_H
#define pinout_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include "SystemState.h"

class Pinout
{
private:
public:
    static String html;
    static String generateHTML();
    static String generateHTML(String popupScript); 
    static String generateHTMLWithPopup(String popupType, String popupMessage);
    static String pageContent();
    static String pageContentCss();
};
#endif