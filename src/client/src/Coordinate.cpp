// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/Coordinate.h"

int Coordinate::getRow() const {
  return row;
}

int Coordinate::getCol() const {
  return col;
}

Coordinate::Coordinate(int row, int col) {
  this->row = row;
  this->col = col;
}

bool Coordinate::isEqual(Coordinate coordinate) const {
  return this->row == coordinate.getRow() && this->col == coordinate.getCol();
}
