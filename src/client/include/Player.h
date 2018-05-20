// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_PLAYER_H
#define EX02_PLAYER_H

#include "Board.h"
#include "Cell.h"
#include "Coordinate.h"
#include "BoardLogic.h"
#include "Display.h"
#include <vector>
#include <iostream>

typedef enum player_type { LOCAL, AI, REMOTE } player_type;

class Player {
 protected:
  BoardLogic board_logic;
  char sign;
  player_type type;
 public:
  /**
   * Returns a coordinate of the chosen move.
   */
  virtual Coordinate playOneTurn(Board &board_copy,
                                 char *message,
                                 vector<Move> &available_moves) = 0;
  virtual void setSign(char sign = EMPTY) = 0;
  virtual char getSign() const = 0;
  virtual player_type getType();
  virtual void endGame() = 0;
};

#endif //EX02_PLAYER_H
