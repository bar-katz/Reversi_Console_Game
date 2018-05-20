//
// Created by Eden Yefet
//

#ifndef REVERSI_CLOSEOTHERSOCKETTASK_H
#define REVERSI_CLOSEOTHERSOCKETTASK_H

#include "../include/MenuItem.h"
#include "../include/RemotePlayer.h"

class CloseOtherSocketTask : public MenuItem {
 private:
  RemotePlayer *remote_player;
 public:
  CloseOtherSocketTask(RemotePlayer *remote_player);
  ~CloseOtherSocketTask();
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_CLOSEOTHERSOCKETTASK_H
