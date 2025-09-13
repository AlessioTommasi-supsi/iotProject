#ifndef OUTVIEW_H
#define OUTVIEW_H

#include <Arduino.h>
#include "viewGeneric.h"
#include "cssControlGroup.h"

class outView {
public:
    static const int PIN_25 = 25;
    static const int PIN_26 = 26;
    static String generateHTML(String signalType, String popupScript = "");
    static String generatePopupPage(String signalType, String message, String redirectPage);
};

#endif