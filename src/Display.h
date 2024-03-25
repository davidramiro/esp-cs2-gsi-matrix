#pragma once

#include "GameState.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoLog.h>

const uint16_t BLACK = 0x0;
const uint16_t GREEN = 0x07E0;
const uint16_t BLUE = 0x001F;
const uint16_t RED = 0xF800;
const uint16_t ORANGE = 0xFCA0;
const uint16_t WHITE = 0xFFFF;
const uint16_t PURPLE = 0xF81F;

class Display {
public:
  Display(int pin, int width, int height, int brightness);

  void updateDisplay(GameState &gameState);

  void showText(const char *text, int pause);

private:
  Adafruit_NeoMatrix *matrix;
};
