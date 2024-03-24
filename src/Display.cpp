#include "Display.h"
#include "main.h"

Display::Display(int pin, int width, int height, int brightness) {
  matrix = new Adafruit_NeoMatrix(width, height, pin,
                                  NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
                                      NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                                  NEO_GRB + NEO_KHZ800);
  matrix->begin();
  matrix->clear();
  matrix->setBrightness(brightness);
  matrix->show();
}

void Display::updateDisplay(GameState &gameState) {

  Log.verboseln("updating display from game state");

  if (gameState.roundPhaseIsUpdated()) {
    Log.verboseln("round phase update required");
    Log.verboseln("stored round phase: %s", gameState.getPhase().c_str());
    if (gameState.getPhase() == "live") {
      this->matrix->fillRect(0, 2, MATRIX_WIDTH, MATRIX_HEIGHT - 2, GREEN);
    } else if (gameState.getPhase() == "freezetime") {
      this->matrix->fillRect(0, 2, MATRIX_WIDTH, MATRIX_HEIGHT - 2, PURPLE);
    } else if (gameState.getPhase() == "over") {
      this->matrix->fillRect(0, 2, MATRIX_WIDTH, MATRIX_HEIGHT - 2, RED);
    }
  }

  if (gameState.roundWinTeamIsUpdated()) {
    Log.verboseln("round win update required");
    Log.verboseln("stored round win: %s", gameState.getWinTeam().c_str());
    if (gameState.getWinTeam().compare("CT") == 0) {
      this->matrix->fillRect(0, 2, MATRIX_WIDTH, MATRIX_HEIGHT - 2, BLUE);
    }
    if (gameState.getWinTeam().compare("T") == 0) {
      this->matrix->fillRect(0, 2, MATRIX_WIDTH, MATRIX_HEIGHT - 2, ORANGE);
    }
  }

  if (gameState.playerHealthIsUpdated() && gameState.getHealth() != 0) {
    Log.verboseln("player health update required");
    Log.verboseln("stored health: %d", gameState.getHealth());

    int barWidth = gameState.getHealth() * MATRIX_WIDTH / 100;
    Log.infoln("drawing health %d with width %d", gameState.getHealth(),
               barWidth);
    int greenVal = gameState.getHealth() * 255 / 100;
    int redVal = 255 - greenVal;

    this->matrix->drawFastHLine(0, 0, barWidth,
                                matrix->Color(redVal, greenVal, 0));

    if (barWidth != MATRIX_WIDTH) {
      this->matrix->drawFastHLine(barWidth, 0, MATRIX_WIDTH - barWidth, BLACK);
    }
  }

  if (gameState.playerAmmoIsUpdated() && gameState.getAmmoMax() != 0) {
    Log.verboseln("player ammo update required");
    Log.verboseln("stored ammo clip: %d, max %d", gameState.getAmmoClip(),
                  gameState.getAmmoMax());

    int ammoPercentage =
        (gameState.getAmmoClip() * 100) / gameState.getAmmoMax();

    int barWidth = ammoPercentage * MATRIX_WIDTH / 100;

    int greenVal = ammoPercentage * 255 / 100;
    int redVal = 255 - greenVal;

    Log.infoln("drawing %d percent ammo with width %d", ammoPercentage,
               barWidth);
    this->matrix->drawFastHLine(0, 1, barWidth,
                                matrix->Color(redVal, greenVal, 0));
    if (barWidth != MATRIX_WIDTH) {
      this->matrix->drawFastHLine(barWidth, 1, MATRIX_WIDTH - barWidth, BLACK);
    }
  }

  gameState.setUpdateFinished();
  this->matrix->show();
}

void Display::showText(const char *text, int pause) {
  for (uint i = 0; i < strlen(text); i++) {
    this->matrix->clear();
    this->matrix->setCursor(1, 0);
    this->matrix->print(text[i]);
    this->matrix->show();
    delay(pause);
  }

  this->matrix->clear();
  this->matrix->show();
}