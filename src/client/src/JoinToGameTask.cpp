//
// Created by Eden Yefet
//

#include "../include/JoinToGameTask.h"

kMenuVal JoinToGameTask::execute() {
  this->remote_player->joinAnExistingRoom();
  return kPlay;
}

JoinToGameTask::JoinToGameTask(RemotePlayer *remote_player) {
  this->remote_player = remote_player;
  title = "Join an existing game room!";
}

string JoinToGameTask::getTitle() {
  return this->title;
}
