// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_GAME_H
#define EX02_GAME_H

#include "Board.h"
#include "GameLogic.h"
#include "Display.h"
#include "Counter.h"
#include "TwoPlayers.h"

class Game {
 private:
  Board *board;
  GameLogic *game_logic;
  Display *display;
  TwoPlayers *two_players;
  ScoreTracker *score_tracking_listener;
  void initializeGame(TwoPlayers *twoPlayers, int board_size);
  void resetGame();

 public:
  Game(Display *display);
  void startNewGame(TwoPlayers *twoPlayers, int board_size);
};

#endif //EX02_GAME_H
