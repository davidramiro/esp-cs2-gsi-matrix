#include "Display.h"
#include "main.h"

Display::Display() {

  screen.init();
  screen.setRotation(1);
  screen.setColorDepth(24);

  screen.fillScreen(TFT_BLACK);
  screen.fillScreen();
  screen.setBrightness(18);

  screen.setFont(&fonts::DejaVu18);
}

void Display::updateDisplay(GameState &gameState) {

  Log.verboseln("updating display from game state");

  if (gameState.roundPhaseIsUpdated()) {
    Log.verboseln("round phase update required");
    Log.verboseln("stored round phase: %s", gameState.getPhase().c_str());
    if (gameState.getPhase() == "live") {
      this->screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
    // } else if (gameState.getPhase() == "freezetime") {
    //   // this->screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);
    } else if (gameState.getPhase() == "over") {
      this->screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
    }
  }

  if (gameState.roundWinTeamIsUpdated()) {
    Log.verboseln("round win update required");
    Log.verboseln("stored round win: %s", gameState.getWinTeam().c_str());
    if (gameState.getWinTeam() == "CT") {
      this->screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLUE);
      this->drawLargeTextTop("CT win", TFT_BLUE);
    }
    if (gameState.getWinTeam() == "T") {
      this->screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_ORANGE);
      this->drawLargeTextTop("T win", TFT_ORANGE);
    }
  }

  if (gameState.playerHealthIsUpdated() && gameState.getHealth() != 0) {
    Log.verboseln("player health update required");
    Log.verboseln("stored health: %d", gameState.getHealth());

    int barWidth = gameState.getHealth() * SCREEN_WIDTH / 100;
    Log.infoln("drawing health %d with width %d", gameState.getHealth(),
               barWidth);
    int greenVal = gameState.getHealth() * 255 / 100;
    int redVal = 255 - greenVal;

    this->screen.drawFastHLine(0, 10, barWidth,
      LGFX::color565(redVal, greenVal, 0));

    if (barWidth != SCREEN_WIDTH) {
      this->screen.drawFastHLine(barWidth, 10, SCREEN_WIDTH - barWidth, BLACK);
    }
  }

  if (gameState.playerAmmoIsUpdated() && gameState.getAmmoMax() != 0) {
    Log.verboseln("player ammo update required");
    Log.verboseln("stored ammo clip: %d, max %d", gameState.getAmmoClip(),
                  gameState.getAmmoMax());

    int ammoPercentage =
        (gameState.getAmmoClip() * 100) / gameState.getAmmoMax();

    int barWidth = ammoPercentage * SCREEN_WIDTH / 100;

    int greenVal = ammoPercentage * 255 / 100;
    int redVal = 255 - greenVal;

    Log.infoln("drawing %d percent ammo with width %d", ammoPercentage,
               barWidth);
    this->screen.drawFastHLine(10, 20, barWidth,
                                screen.color565(redVal, greenVal, 0));
    if (barWidth != SCREEN_WIDTH) {
      this->screen.drawFastHLine(barWidth, 20, SCREEN_WIDTH - barWidth, BLACK);
    }
  }

  gameState.setUpdateFinished();
}

void Display::displayConnectionInfo(const char *ssid, const char *ip) {
    screen.setFont(&fonts::DejaVu12);

    this->screen.drawFastHLine(0, 95, SCREEN_WIDTH, TFT_WHITE);
    this->screen.setTextSize(1);
    this->screen.setCursor(0, 100);
    this->screen.print("Connected to: ");
    this->screen.println(ssid);
    this->screen.print("IP: ");
    this->screen.print(ip);
}

void Display::drawMediumText(const char *text) {
  this->screen.clear();

  screen.setFont(&fonts::DejaVu18);

  this->screen.setTextSize(1);
  this->screen.setCursor(5, 10);
  this->screen.print(text);
}

void Display::drawLargeTextTop(const char *text, const int bgcolor) {
  screen.setFont(&fonts::DejaVu24);

  this->screen.setTextColor(TFT_WHITE, bgcolor);
  this->screen.setTextSize(2);
  this->screen.setCursor(120 - 14 * (strlen(text)), 45);
  this->screen.print(text);
}

void Display::colorFill(int color) {
  this->screen.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}