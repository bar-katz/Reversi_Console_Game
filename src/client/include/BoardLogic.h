// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_BOARDLOGIC_H
#define EX02_BOARDLOGIC_H

#include <vector>
#include "Board.h"
#include "Cell.h"
#include "Move.h"
#include "ScoreTracker.h"

class BoardLogic {
 private:
  /**
   * Searches around a given and updates the available_moves and
   * disks_to_flip vectors. This function uses searchOneDirection for better
   * readability and OOP design.
   */
  void searchAround(Board &board,
                    int row,
                    int col,
                    vector<Move> &available_moves,
                    vector<Cell *> &disks_to_flip);

  /**
   * This function is called from searchAround, and checks one direction for
   * available moves and cells to flip.
   */
  void searchOneDirection(int dy,
                          int dx,
                          Board &board,
                          vector<Move> &available_moves,
                          Cell *original_cell,
                          vector<Cell *> &disks_to_flip);

  void mergeVectorsWithoutDuplicates(std::vector<Move> &v1,
                                     std::vector<Move> &v2);
 public:
  BoardLogic();
  vector<Move> getValidMoves(Board &board, char current_player);
  int updateBoardFromMove(Board &board,
                          ScoreTracker *score_tracker,
                          Cell *player_move,
                          char player);
  char getOppositeSign(char player_sign);
};

#endif //EX02_BOARDLOGIC_H
