// Eden Yefet 204778294
// Bar Katz 208561357

#include <fstream>
#include "../include/LocalVersusLocalChoice.h"
#include "../include/LocalVersusRemoteChoice.h"
#include "../include/Menu.h"
#include "../include/LocalVersusAIChoice.h"
#include "../include/QuitGameChoice.h"
#include "../include/ConsoleDisplay.h"

#define BOARD_SIZE 4

int main() {

  Display *console_display = new ConsoleDisplay();
  Game *my_game = new Game(console_display);
  int board_size = 4;
  // Creates a menu with options
  Menu menu = Menu("Hello", console_display);
  MenuItem *local_vs_local = new LocalVersusLocalChoice(my_game, board_size);
  MenuItem *local_vs_ai = new LocalVersusAIChoice(my_game, board_size);
  MenuItem *local_vs_remote = new LocalVersusRemoteChoice(my_game,
                                                          board_size,
                                                          console_display);
  MenuItem *quit_game = new QuitGameChoice();

  menu.addMenuItem(local_vs_local);
  menu.addMenuItem(local_vs_ai);
  menu.addMenuItem(local_vs_remote);
  menu.addMenuItem(quit_game);

  menu.startMenu();

  delete quit_game;
  delete local_vs_remote;
  delete local_vs_ai;
  delete local_vs_local;
  delete my_game;
  delete console_display;
  return 0;
}