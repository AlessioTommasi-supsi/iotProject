#ifndef VIEW_MULTIPLEX_H
#define VIEW_MULTIPLEX_H

#include <Arduino.h>
#include "viewGeneric.h"
#include "cssToggleButton.h"
#include "cssMultiplexLayout.h"
#include "cssStatusIndicator.h"
#include "cssControlGroup.h"


class viewMultiplex
{
private:
    /* data */
public:

    static String Config();

    static String pageContent();

    static String pinStartAndStopForm(int channelAdsNumber, String signalType);
};

#endif