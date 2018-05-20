//
// Created by Eden Yefet
//

#ifndef REVERSI_JOINTOGAMETASK_H
#define REVERSI_JOINTOGAMETASK_H

#include <sstream>
#include "../include/MenuItem.h"
#include "../include/RemotePlayer.h"

class JoinToGameTask : public MenuItem {
 private:
  string title;
  Display *display;
  RemotePlayer *remote_player;
 public:
  JoinToGameTask(RemotePlayer *remote_player);
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_JOINTOGAMETASK_H
