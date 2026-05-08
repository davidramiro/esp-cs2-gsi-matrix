#include "Display.h"
#include "LVGL_Display.h"
#include "main.h"
#include "ui/ui.h"
#include "ui/vars.h"

Display::Display()= default;

void Display::updateDisplay(GameState &gameState) {

  if (gameState.roundPhaseIsUpdated()) {
    if (gameState.getPhase() == "live") {
      loadScreen(SCREEN_ID_ROUND_START);
    } else if (gameState.getPhase() == "freezetime") {
      loadScreen(SCREEN_ID_FREEZETIME);
    }
  }

  if (gameState.roundWinTeamIsUpdated()) {
    if (gameState.getWinTeam() == "CT") {
      loadScreen(SCREEN_ID_CT_WIN);
    }
    if (gameState.getWinTeam() == "T") {
      loadScreen(SCREEN_ID_T_WIN);
    }
  }

  if (gameState.bombStatusIsUpdated()) {
    if (gameState.getBombStatus() == "planted") {
      set_var_bomb_timer(80);
      loadScreen(SCREEN_ID_BOMB);
    }
  }

  gameState.setUpdateFinished();
}