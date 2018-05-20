//
// Created by Eden Yefet
//

#include "../include/StartNewRemoteGameTask.h"

kMenuVal StartNewRemoteGameTask::execute() {
  this->remote_player->startANewRoom();

  return kPlay;
}

string StartNewRemoteGameTask::getTitle() {
  return this->title;
}

StartNewRemoteGameTask::StartNewRemoteGameTask(RemotePlayer *remote_player) {
  this->remote_player = remote_player;
  title = "Start a new game room!";
}
