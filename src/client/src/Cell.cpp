// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/Cell.h"

int Cell::getRow() const {
  return row;
}

int Cell::getColumn() const {
  return column;
}

Cell::Cell(int row, int column) {
  this->row = row;
  this->column = column;
  this->sign = EMPTY;
}

char Cell::getSign() const {
  return sign;
}

void Cell::setSign(char sign) {
  Cell::sign = sign;

}

Cell::Cell(int row, int column, char sign) {
  this->row = row;
  this->column = column;
  this->sign = sign;
}

bool Cell::isEqual(Cell other) {
  return this->row == other.getRow() && this->column == other.getColumn();
}

ostream &operator<<(ostream &stream, const Cell &cell) {
  return stream << "(" << cell.row << "," << cell.column << ")";
}

Cell::~Cell() {

}

