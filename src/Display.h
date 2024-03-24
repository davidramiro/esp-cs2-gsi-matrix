#pragma once

#include "GameState.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoLog.h>

const uint16_t BLACK = uint16_t(0x0);
const uint16_t GREEN = uint16_t(0x00FF00);
const uint16_t BLUE = uint16_t(0x0000FF);
const uint16_t RED = uint16_t(0xFF0000);
const uint16_t ORANGE = uint16_t(0xFF8800);
const uint16_t WHITE = uint16_t(0xFFFFFF);
const uint16_t PURPLE = uint16_t(0xAF00AF);

class Display {
public:
  Display(int pin, int width, int height, int brightness);

  void updateDisplay(GameState &gameState);

  void showText(const char *text, int pause);

private:
  Adafruit_NeoMatrix *matrix;
};
