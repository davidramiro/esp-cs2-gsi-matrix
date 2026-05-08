#pragma once

#include "GameState.h"
#include "LGFX_Config.hpp"
#include <SPI.h>

class Display {
public:
  Display();

  void updateDisplay(GameState &gameState);
};
