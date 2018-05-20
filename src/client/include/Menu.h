// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_MENU_H
#define REVERSI_MENU_H

#include "../include/Display.h"
#include "../include/Player.h"
#include "MenuItem.h"
#include "Game.h"
#include <limits>
#include "../include/LocalPlayer.h"
using namespace std;

class Menu {
 private:
  Game game;
  string menu_title;
  vector<MenuItem *> menu_items;
  Display *display;

 public:
  Menu(string menu_title, Display *display);
  void addMenuItem(MenuItem *menu_item);
  ~Menu();
  void *startMenu();
};

#endif //REVERSI_MENU_H
