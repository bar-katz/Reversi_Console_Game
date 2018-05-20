// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/TwoPlayers.h"

Player *TwoPlayers::getP1() const {
  return p1;
}

Player *TwoPlayers::getP2() const {
  return p2;
}

TwoPlayers::TwoPlayers(Player *p1, Player *p2) {
  this->p1 = p1;
  this->p2 = p2;
}

TwoPlayers::~TwoPlayers() {
  delete p1;
  delete p2;
}
