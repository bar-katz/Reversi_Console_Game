// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_SINGLEPLAYERGAMECHOICE_H
#define REVERSI_SINGLEPLAYERGAMECHOICE_H

#include "MenuItem.h"
#include "Game.h"
#include <iostream>
#include "../include/Player.h"
#include "../include/LocalPlayer.h"

using namespace std;

class LocalVersusLocalChoice : public MenuItem {
 private:
  Game *game;
  int board_size;
 public:
  LocalVersusLocalChoice(Game *game, int board_size);
  virtual kMenuVal execute();
  virtual string getTitle();
  ~LocalVersusLocalChoice();
};

#endif //REVERSI_SINGLEPLAYERGAMECHOICE_H
