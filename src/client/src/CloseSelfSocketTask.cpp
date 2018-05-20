//
// Created by Eden Yefet
//

#include "../include/CloseSelfSocketTask.h"

string CloseSocketTask::getTitle() {
  return "Return to Main Menu";
}

kMenuVal CloseSocketTask::execute() {
  this->remote_player->closeSocket();
  return kQuit;
}

CloseSocketTask::~CloseSocketTask() {

}

CloseSocketTask::CloseSocketTask( RemotePlayer *remote_player) {
  this->remote_player = remote_player;
}
