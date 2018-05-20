// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_LOCALVERSUSAICHOICE_H
#define REVERSI_LOCALVERSUSAICHOICE_H

#include "../include/Player.h"
#include "../include/LocalPlayer.h"
#include "../include/AIPlayer.h"
#include "MenuItem.h"
#include "TwoPlayers.h"
#include "Game.h"

using namespace std;

class LocalVersusAIChoice : public MenuItem {
 private:
  Game *game;
  int board_size;
 public:
  LocalVersusAIChoice(Game *game, int board_size);
  ~LocalVersusAIChoice();
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_LOCALVERSUSAICHOICE_H
