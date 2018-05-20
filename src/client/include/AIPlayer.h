// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_AIPLAYER_H
#define EX02_AIPLAYER_H

#include "Player.h"
#include "Move.h"
#include <cmath>

class AIPlayer : public Player {
 private:
  /**
   * Simulates a move on a given board and finds the maximum possible move for
   * the opponent.
   * opponent on its upcoming
   * @return An integer representing the best move score for the opponent
   */
  int simulateMove(Cell *choice, Board &current_board);
 public:
  AIPlayer();
  /**
   * Returns a move using Minimax algorithm.
   */
  virtual Coordinate playOneTurn(Board &board_copy,
                                 char *message,
                                 vector<Move> &available_moves);
  virtual void setSign(char sign);
  virtual char getSign() const;
  void endGame();
};

#endif //EX02_AIPLAYER_H
