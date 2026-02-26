#pragma once

#include "GameState.h"
#include <LovyanGFX.hpp>
#include "LGFX_Config.hpp"
#include <SPI.h>
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
  Display();

  void updateDisplay(GameState &gameState);

  void displayConnectionInfo(const char *ssid, const char *ip);
  void drawMediumText(const char *text);
  void drawLargeTextTop(const char *text, const int bgcolor);
  void colorFill(int color);

private:
  LGFX screen;
};
