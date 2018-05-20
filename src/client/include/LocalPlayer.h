// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_LOCALPLAYER_H
#define EX02_LOCALPLAYER_H

#include "Player.h"
#include "Board.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <limits>
#include <cstring>
#include <sstream>

class LocalPlayer : public Player {
 public:
  LocalPlayer();
  Coordinate playOneTurn(Board &board_copy,
                         char *message,
                         vector<Move> &available_moves);
  void setSign(char sign);
  char getSign() const;
  void endGame();
};

#endif //EX02_LOCALPLAYER_H
