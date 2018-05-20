// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_MOVE_H
#define EX02_MOVE_H

#include "Coordinate.h"

class Move {
 private:
  int score;
  Coordinate coordinate;

 public:
  Move(Coordinate coordinate, int score);
  int getScore() const;
  void setScore(int score);
  int getRow();
  int getColumn();
  bool isEqual(Move other);
  const Coordinate &getCoordinate() const;
};

#endif //EX02_MOVE_H
