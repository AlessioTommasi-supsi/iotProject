#ifndef viewGraph_H
#define viewGraph_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include <set> 
#include "SystemState.h"

class viewGraph
{
private:
public:
    static String html;
    static String generateHTML();
    static String generateGraph(std::vector<int> addresses, String apiFetch, String apiFetchParam);
    static String generateSelectorHTML(std::vector<int> addresses);
    static String generateBasicJavaScript();
    static String generateDrawFunctionJS();
    static String generateUpdateFunctionJS(String apiFetch, String apiFetchParam);
    static String generateGraphExportJS(String apiFetch, String apiFetchParam);
    static String generateInitializationJS();
    static String generateCirularProgressBarGraph(String circle_progressbar_label, float circle_progressbar_used_value, float circle_progressbar_total_value);
    static String generateCirularProgressBarGraph(String circle_progressbar_label, float circle_progressbar_used_value, float circle_progressbar_total_value, String apiFetchData, int timeToUpdate);
    static String initCirularProgressBarGraph();
    static String endCirularProgressBarGraph();
};

#endif