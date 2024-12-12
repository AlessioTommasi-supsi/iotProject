#ifndef DISPLAYOLED_H
#define DISPLAYOLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width
#define SCREEN_HEIGHT 64 // OLED display height

void setupDisplay();
void printOnDisplay(String text);

extern Adafruit_SSD1306 display;

#endif
