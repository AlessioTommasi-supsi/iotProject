#include "ADS1115_model.h"
#include "SystemState.h"

void ADS1115_model::setChannel(int channel) {
    // Imposta il canale del multiplexer (mappa completa da 0 a 7)
    Pin &pinA = SystemState::getInstance()->pinoutData->getPin(PIN_A);
    Pin &pinB = SystemState::getInstance()->pinoutData->getPin(PIN_B);
    Pin &pinC = SystemState::getInstance()->pinoutData->getPin(PIN_C);

    switch (channel)
    {
        case 0:
            pinA.write(false);
            pinB.write(false);
            pinC.write(false);
            break;
        case 1:
            pinA.write(true);
            pinB.write(false);
            pinC.write(false);
            break;
        case 2:
            pinA.write(false);
            pinB.write(true);
            pinC.write(false);
            break;
        case 3:
            pinA.write(true);
            pinB.write(true);
            pinC.write(false);
            break;
        case 4:
            pinA.write(false);
            pinB.write(false);
            pinC.write(true);
            break;
        case 5:
            pinA.write(true);
            pinB.write(false);
            pinC.write(true);
            break;
        case 6:
            pinA.write(false);
            pinB.write(true);
            pinC.write(true);
            break;
        case 7:
            pinA.write(true);
            pinB.write(true);
            pinC.write(true);
            break;
        default:
            // Se il canale non è valido, non eseguire nulla
            break;
    }
}