#include "./model/LedEsp32.h"

static void LedEsp32::blinkTaskFunction(void *parameter)
{
    LedEsp32 *LedEsp32 = static_cast<LedEsp32 *>(parameter);
    for (;;)
    {
        LedEsp32->turnOn();
        vTaskDelay(pdMS_TO_TICKS(LedEsp32->blinkSpeed));
        LedEsp32->turnOff();
        vTaskDelay(pdMS_TO_TICKS(LedEsp32->blinkSpeed));
    }
}

LedEsp32::LedEsp32(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void LedEsp32::turnOn()
{
    digitalWrite(pin, HIGH);
}

void LedEsp32::turnOff()
{
    digitalWrite(pin, LOW);
}

void LedEsp32::blink()
{
    xTaskCreatePinnedToCore(blinkTaskFunction, "blinkTask", 1000, this, 1, &blinkTask, 1);
}

void LedEsp32::blink(float speed)
{
    blinkSpeed = (int)(1000 / (speed * 2));
    xTaskCreatePinnedToCore(blinkTaskFunction, "blinkTask", 1000, this, 1, &blinkTask, 1);
}

void LedEsp32::stopBlink()
{
    vTaskDelete(blinkTask);
}

void LedEsp32::actionOK()
{
    stopBlink();
    turnOn();
}

void LedEsp32::actionError()
{
    turnOff();
}