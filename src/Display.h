#pragma once

#include "GameState.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoLog.h>

class Display {
public:
  Display(int pin, int width, int height, int brightness);

  void updateDisplay(GameState &gameState);

  void showText(const char *text, int pause);

private:
  Adafruit_NeoMatrix *matrix;
};
