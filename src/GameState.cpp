#include "GameState.h"

GameState::GameState() : health(0), armor(0) {}

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

void GameState::updatePlayerHealth(int health) {
  this->health = health;
  this->healthUpdated = true;
}

void GameState::updatePlayerAmmoMax(int ammoMax) {
  this->ammoMax = ammoMax;
  this->ammoUpdated = true;
}

void GameState::updatePlayerAmmoClip(int ammoClip) {
  this->ammoClip = ammoClip;
  this->ammoUpdated = true;
}

void GameState::setUpdateFinished() {
  this->armorUpdated = false;
  this->winTeamUpdated = false;
  this->phaseUpdated = false;
  this->healthUpdated = false;
  this->bombUpdated = false;
}

std::string GameState::getPhase() const { return phase; }
std::string GameState::getBombStatus() const { return bombStatus; }
std::string GameState::getWinTeam() const { return winTeam; }
int GameState::getHealth() const { return health; }
int GameState::getAmmoClip() const { return ammoClip; }
int GameState::getAmmoMax() const { return ammoMax; }

bool GameState::roundPhaseIsUpdated() const { return phaseUpdated; };
bool GameState::roundWinTeamIsUpdated() const { return winTeamUpdated; }
bool GameState::bombStatusIsUpdated() const { return bombUpdated; }
bool GameState::playerHealthIsUpdated() const { return healthUpdated; }
bool GameState::playerAmmoIsUpdated() const { return ammoUpdated; }
