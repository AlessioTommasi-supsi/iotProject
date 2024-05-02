#include <Arduino.h>

class Led
{
private:
    int pin;
    TaskHandle_t blinkTask;
    int blinkSpeed = 500; // in millisecondi

    static void blinkTaskFunction(void *parameter)
    {
        Led *led = static_cast<Led *>(parameter);
        for (;;)
        {
            led->turnOn();
            vTaskDelay(pdMS_TO_TICKS(led->blinkSpeed));
            led->turnOff();
            vTaskDelay(pdMS_TO_TICKS(led->blinkSpeed));
        }
    }

public:
    Led(int pin)
    {
        this->pin = pin;
        pinMode(pin, OUTPUT);
    }

    void turnOn()
    {
        digitalWrite(pin, HIGH);
    }

    void turnOff()
    {
        digitalWrite(pin, LOW);
    }

    void blink()
    {
        xTaskCreatePinnedToCore(blinkTaskFunction, "blinkTask", 1000, this, 1, &blinkTask, 1);
    }

    void blink(float speed)
    {
        blinkSpeed = (int)(1000 / (speed * 2));
        xTaskCreatePinnedToCore(blinkTaskFunction, "blinkTask", 1000, this, 1, &blinkTask, 1);
    }

    void stopBlink()
    {
        vTaskDelete(blinkTask);
    }

    virtual void actionOK()
    {
        stopBlink();
        turnOn();
    }

    virtual void actionError()
    {
        turnOff();
    }
};