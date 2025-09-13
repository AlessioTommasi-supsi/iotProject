#ifndef VIEWGENERIC_H
#define VIEWGENERIC_H

#include <Arduino.h>


class viewGeneric
{
    private:

    public:
        static String html;
        
        static String defaultHeader();
        static String defaultHeader(String title);
        static String basicHeader(String title);
        static String defaultCssHeader(String title);
        static String defaultPorfolioCss();
        static String defaultFooter();
        static String addCss();
        static String addFormCss();
        static String addFormStyleCss();
        static String addFieldFormCss();
        static String addFieldFormStyleCss();
        static String addPinCss();
        static String addPinStyleCss();
        static String addNavbarCss();
        static String addNavbarStyleCss();
        static String addNavbar();
        static String dynamicUpdateContent(String divId, String api, int timeToUpdate);
        static String dynamicUpdateContentScript();
        static String fetchContentScript();
        static String addExportCSVScript();
        static String addAutoRefreshControlScript();
};

#endif // !VIEWGENERIC_H#define VIEWGENERIC_H
