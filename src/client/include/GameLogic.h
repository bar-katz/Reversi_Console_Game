// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_GAMELOGIC_H
#define EX02_GAMELOGIC_H

#include "Board.h"
#include "Player.h"
#include "Display.h"
#include "ScoreTracker.h"
#include "BoardLogic.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

class GameLogic {
 private:
  Board *game_board;
  Player *p1;
  Player *p2;
  Player *current_player;
  Display *display;
  ScoreTracker *score_tracker;
  BoardLogic board_logic;
  char message[7];

  void switchTurn();
  bool isValidMove(vector<Move> available_moves, Cell *move);

 public:
  GameLogic(Board *game_board,
            Player *p1,
            Player *p2,
            ScoreTracker *score_tracker,
            Display *display);

  /**
   *Plays one turn in the game, that is to say that the function calls
   * private functions to find available moves, takes user-input and makes
   * the move if valid.
   * @return false if no moves are available, true otherwise.
   */
  bool playOneTurn();
  ScoreTracker *getScoreTracker() const;
  std::string getNameFromChar(char player_sign);
  Player *getCurrentPlayer();
};

#endif //EX02_GAMELOGIC_H
