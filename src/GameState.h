#pragma once

#include <Arduino.h>
#include <string>

class GameState {
public:
  GameState();

  void updateRoundPhase(const char *phase);
  void updateRoundWinTeam(const char *winTeam);
  void updateBombStatus(const char *bombStatus);
  void setHeartbeat();
  void setUpdateFinished();

  std::string getPhase() const;
  std::string getBombStatus() const;
  std::string getWinTeam() const;

  bool roundPhaseIsUpdated() const;
  bool roundWinTeamIsUpdated() const;
  bool bombStatusIsUpdated() const;

  int64_t getLastHeartBeat() const;

private:
  bool phaseUpdated;
  std::string phase;

  int64_t lastHeartBeat;

  bool bombUpdated;
  std::string bombStatus;

  bool winTeamUpdated;
  std::string winTeam;
};
