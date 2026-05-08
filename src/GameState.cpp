#include "GameState.h"

GameState::GameState(){}

void GameState::updateRoundPhase(const char *phase) {
  this->phase = phase;
  phaseUpdated = true;
}

void GameState::updateRoundWinTeam(const char *winTeam) {
  this->winTeam = winTeam;
  this->winTeamUpdated = true;
}

void GameState::updateBombStatus(const char *bombStatus) {
  this->bombStatus = bombStatus;
  this->bombUpdated = true;
}

void GameState::setUpdateFinished() {
  this->winTeamUpdated = false;
  this->phaseUpdated = false;
  this->bombUpdated = false;
}

void GameState::setHeartbeat() {
  this->lastHeartBeat = esp_timer_get_time() / 1000;
}

std::string GameState::getPhase() const { return phase; }
std::string GameState::getBombStatus() const { return bombStatus; }
std::string GameState::getWinTeam() const { return winTeam; }

bool GameState::roundPhaseIsUpdated() const { return phaseUpdated; };
bool GameState::roundWinTeamIsUpdated() const { return winTeamUpdated; }
bool GameState::bombStatusIsUpdated() const { return bombUpdated; }

int64_t GameState::getLastHeartBeat() const {
  return lastHeartBeat;
}
