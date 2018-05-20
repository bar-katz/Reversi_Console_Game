// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_LOCALVERSUSREMOTECHOICE_H
#define REVERSI_LOCALVERSUSREMOTECHOICE_H

#include "../include/RemotePlayer.h"
#include "../include/LocalPlayer.h"
#include "../include/Player.h"
#include <fstream>
#include "../include/StartNewRemoteGameTask.h"
#include "../include/JoinToGameTask.h"
#include "MenuItem.h"
#include "Game.h"

class LocalVersusRemoteChoice : public MenuItem {
 private:
  Game *game;
  int board_size;
  vector<MenuItem *> sub_menu_items;
  TwoPlayers * two_players;
  LocalPlayer *local_player;
  RemotePlayer *remote_player;

  kMenuVal startSubMenu();
  Display *display;
 public:
  LocalVersusRemoteChoice(Game *game, int board_size, Display *display);
  virtual kMenuVal execute();
  virtual string getTitle();
  ~LocalVersusRemoteChoice();
};

#endif //REVERSI_LOCALVERSUSREMOTECHOICE_H
