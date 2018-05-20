// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/Move.h"

int Move::getScore() const {
  return score;
}

void Move::setScore(int score) {
  this->score = score;
}

bool Move::isEqual(Move other) {
  return this->getRow() == other.getRow()
      && this->getColumn() == other.getColumn();
}

Move::Move(Coordinate coordinate, int score)
    : coordinate(coordinate), score(score) {
}

int Move::getRow() {
  return this->coordinate.getRow();
}

int Move::getColumn() {
  return this->coordinate.getCol();
}

const Coordinate &Move::getCoordinate() const {
  return coordinate;
}
