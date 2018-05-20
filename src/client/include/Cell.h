// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_CELL_H
#define EX02_CELL_H

#include <iostream>

#define WHITE 'O'
#define BLACK 'X'
#define TIE 'T'
#define EMPTY ' '
#define AVAILABLE_MOVE '*'
using namespace std;

class Cell {
 private:
  int row;
  int column;
  char sign;
  friend ostream &operator<<(ostream &, const Cell &);

  // Cell branch
 public:
  ~Cell();
  char getSign() const;
  void setSign(char sign);
  int getRow() const;
  int getColumn() const;
  Cell(int row, int column);
  Cell(int row, int column, char sign);
  bool isEqual(Cell other);

  bool operator==(const Cell &other) {
    return (this->column == other.column) && (this->row == other.row);
  }
};

#endif //EX02_CELL_H
