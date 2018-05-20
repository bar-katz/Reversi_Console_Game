//
// Created by Eden Yefet
//

#ifndef REVERSI_CLOSESOCKETTASK_H
#define REVERSI_CLOSESOCKETTASK_H

#include "../include/MenuItem.h"
#include "RemotePlayer.h"

class CloseSocketTask : public MenuItem {
 private:
  RemotePlayer *remote_player;
 public:
  CloseSocketTask( RemotePlayer *remote_player);
  ~CloseSocketTask();
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_CLOSESOCKETTASK_H
