//
// Created by Eden Yefet
//

#ifndef REVERSI_QUITGAMECHOICE_H
#define REVERSI_QUITGAMECHOICE_H

#include "../include/MenuItem.h"

class QuitGameChoice: public MenuItem {
 public:
  QuitGameChoice();
  ~QuitGameChoice();
  virtual kMenuVal execute();
  virtual string getTitle();
};

#endif //REVERSI_QUITGAMECHOICE_H
