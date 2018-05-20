// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_CONSOLEDISPLAY_H
#define EX02_CONSOLEDISPLAY_H

#include "Display.h"

class ConsoleDisplay : public Display {
 public:
  void printBoard(Board *board);
  ConsoleDisplay();
  virtual void print(ostream &message);
};

#endif //EX02_CONSOLEDISPLAY_H
