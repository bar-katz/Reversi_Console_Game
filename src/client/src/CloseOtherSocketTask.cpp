//
// Created by Eden Yefet
//


#include "../include/CloseOtherSocketTask.h"

CloseOtherSocketTask::CloseOtherSocketTask(RemotePlayer *remote_player) {
  this->remote_player = remote_player;
}

CloseOtherSocketTask::~CloseOtherSocketTask() {

}

kMenuVal CloseOtherSocketTask::execute() {
  this->remote_player->closeOtherSocket();
  return kQuit;
}

string CloseOtherSocketTask::getTitle() {
  return "Close other game";
}
