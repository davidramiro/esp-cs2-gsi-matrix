#pragma once

#include <Arduino.h>
#include <string>

class GameState {
public:
  GameState();

  void updateRoundPhase(const char *phase);
  void updateRoundWinTeam(const char *winTeam);
  void updateBombStatus(const char *bombStatus);
  void updatePlayerHealth(int health);
  void updatePlayerAmmoMax(int ammoMax);
  void updatePlayerAmmoClip(int ammoClip);
  void setUpdateFinished();

  std::string getPhase() const;
  std::string getBombStatus() const;
  std::string getWinTeam() const;
  int getHealth() const;
  int getArmor() const;
  int getAmmoClip() const;
  int getAmmoMax() const;

  bool roundPhaseIsUpdated() const;
  bool roundWinTeamIsUpdated() const;
  bool bombStatusIsUpdated() const;
  bool playerHealthIsUpdated() const;
  bool playerAmmoIsUpdated() const;

private:
  bool phaseUpdated;
  std::string phase;

  bool bombUpdated;
  std::string bombStatus;

  bool winTeamUpdated;
  std::string winTeam;

  bool healthUpdated;
  int health;

  bool armorUpdated;
  int armor;

  bool ammoUpdated;
  int ammoClip;
  int ammoMax;
};
