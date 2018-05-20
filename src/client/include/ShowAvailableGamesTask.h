//
// Created by Eden Yefet
//

#ifndef REVERSI_SHOWAVAILABLEGAMESTASK_H
#define REVERSI_SHOWAVAILABLEGAMESTASK_H

#include "../include/MenuItem.h"
#include "../include/RemotePlayer.h"

class ShowAvailableGamesTask : public MenuItem {
  Display *display;
  RemotePlayer *remote_player;
 public:
  ShowAvailableGamesTask(RemotePlayer *remote_player);
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_SHOWAVAILABLEGAMESTASK_H
