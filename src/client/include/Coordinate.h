// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_COORDINATE_H
#define EX02_COORDINATE_H

class Coordinate {
 private:
  int row;
  int col;

 public:
  Coordinate(int row, int col);
  int getRow() const;
  int getCol() const;
  bool isEqual(Coordinate coordinate) const;

};

#endif //EX02_COORDINATE_H
