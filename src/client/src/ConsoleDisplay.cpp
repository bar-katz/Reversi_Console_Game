// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/ConsoleDisplay.h"

ConsoleDisplay::ConsoleDisplay() {

}

void ConsoleDisplay::printBoard(Board *board) {
  int size = board->getSize();
  Cell ***grid = board->getGrid();

  cout << endl;
  for (int col_number = 0; col_number < size + 1; col_number++) {
    cout << " " << col_number << " |";
  }

  cout << endl;
  for (int space = 0; space < size + 1; space++) {
    cout << "----";
  }

  cout << endl;
  for (int row = 0; row < size; row++) {
    cout << " " << row + 1 << " |";
    for (int col = 0; col < size; col++) {
      cout << " " << grid[row][col]->getSign() << " |";
    }
    cout << endl;
    for (int space = 0; space < size + 1; space++) {
      cout << "----";
    }

    cout << endl;
  }
}

void ConsoleDisplay::print(ostream &message) {
  message;
}
