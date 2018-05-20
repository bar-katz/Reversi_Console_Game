// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_MENUITEM_H
#define REVERSI_MENUITEM_H
#include <iostream>
#include "../include/Player.h"
#include "TwoPlayers.h"

typedef enum kMenuVal { kPlay, kQuit, kContinue } kMenuVal;
using namespace std;

class MenuItem {
 public:
  virtual kMenuVal execute() = 0;
  virtual string getTitle() = 0;
  virtual ~MenuItem(){};
};

#endif //REVERSI_MENUITEM_H
