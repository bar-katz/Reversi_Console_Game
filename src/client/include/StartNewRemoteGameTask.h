//
// Created by Eden Yefet
//

#ifndef REVERSI_STARTNEWREMOTEGAMETASK_H
#define REVERSI_STARTNEWREMOTEGAMETASK_H

#include <sstream>
#include "../include/MenuItem.h"
#include "../include/RemotePlayer.h"

class StartNewRemoteGameTask : public MenuItem {
 private:
  string title;
  Display *display;
  RemotePlayer *remote_player;
 public:
  StartNewRemoteGameTask(RemotePlayer *remote_player);
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_STARTNEWREMOTEGAMETASK_H
