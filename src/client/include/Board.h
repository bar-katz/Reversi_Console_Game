// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX01_BOARD_H
#define EX01_BOARD_H

#include <iostream>
#include <vector>
#include "Cell.h"
#include "Move.h"
#include "Coordinate.h"

using namespace std;

class Board {
 private:
  Cell ***grid;
  int size;

 public:
  explicit Board(int size);
  ~Board();
  int getSize() const;
  Cell ***getGrid() const;
  Cell *getCell(int row, int col);

  // Returns a Board object with the values of the available moves cells set
  // to the '*' sign in order to be more user-friendly.
  Board getBoardWithMoves(vector<Move> available_moves);
  Board copy();

  Cell *coordinateToCell(Coordinate coordinate);
};

#endif //EX01_BOARD_H
