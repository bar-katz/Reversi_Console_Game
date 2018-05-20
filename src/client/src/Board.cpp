// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/Board.h"

Board::Board(int size) : size(size) {

  // creates 2D grid of Cells
  this->grid = new Cell **[size];
  for (int i = 0; i < size; i++) {
    this->grid[i] = new Cell *[size];
    for (int j = 0; j < size; j++) {
      this->grid[i][j] = new Cell(i + 1, j + 1);
    }
  }
}

int Board::getSize() const {
  return size;
}

Cell ***Board::getGrid() const {
  return grid;
}

Board::~Board() {
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      delete this->grid[i][j];
    }
    delete[] this->grid[i];
  }
  delete[] this->grid;
}

Board Board::getBoardWithMoves(vector<Move> available_moves) {
  Board board_copy = this->copy();

  // sets AVAILABLE_MOVE sign on available moves' cells
  for (int i = 0; i < available_moves.size(); i++) {
    int row = available_moves[i].getRow();
    int col = available_moves[i].getColumn();
    board_copy.grid[row - 1][col - 1]->setSign(AVAILABLE_MOVE);
  }

  return board_copy;
}

Cell *Board::coordinateToCell(Coordinate coordinate) {
  if (coordinate.getRow() > size || coordinate.getRow() < 1
      || coordinate.getCol()
          > size || coordinate.getCol() < 1) {
    return NULL;
  }
  return this->grid[coordinate.getRow() - 1][coordinate.getCol() - 1];
}

Cell *Board::getCell(int row, int col) {
  return this->grid[row - 1][col - 1];
}

Board Board::copy() {
  Board board_copy = Board(this->size);

  // creates 2D grid of Cells
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      board_copy.grid[i][j]->setSign(this->grid[i][j]->getSign());
    }
  }
  return board_copy;
}

