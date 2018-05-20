// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_TWOPLAYERS_H
#define REVERSI_TWOPLAYERS_H

#include "../include/Player.h"

class TwoPlayers {
 private:
  Player *p1;
  Player *p2;

 public:
  TwoPlayers(Player *p1, Player *p2);
  Player *getP1() const;
  Player *getP2() const;
  ~TwoPlayers();
};

#endif //REVERSI_TWOPLAYERS_H
