// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_DISPLAY_H
#define EX02_DISPLAY_H

#include "Board.h"

class Display {
 public:
  virtual void printBoard(Board *board) = 0;

  // prints a message
  virtual void print(ostream &stream) = 0;
};

#endif //EX02_DISPLAY_H
