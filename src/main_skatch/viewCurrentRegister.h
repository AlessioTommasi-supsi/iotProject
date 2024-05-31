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
    static String generateHTML();
    static String generateEmptyFormRegister();
    static String generateHTML(String registerAddress, float registerValue);
    static String generateHTMLConfirm(String registerAddress, float registerValue);
};


#endif 