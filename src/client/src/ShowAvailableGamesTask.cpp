//
// Created by Eden Yefet
//

#include "../include/ShowAvailableGamesTask.h"

ShowAvailableGamesTask::ShowAvailableGamesTask(RemotePlayer *remote_player) {
  this->remote_player = remote_player;
}

kMenuVal ShowAvailableGamesTask::execute() {
  this->remote_player->showAvailableRooms();
  return kContinue;
}

string ShowAvailableGamesTask::getTitle() {
  return "Show available games";
}
