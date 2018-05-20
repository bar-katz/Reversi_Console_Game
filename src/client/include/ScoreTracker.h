// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_SCORETRACKINGLISTENER_H
#define EX02_SCORETRACKINGLISTENER_H

#include "../include/Board.h"
#include "Counter.h"

class ScoreTracker {
 private:
  Counter white_disks;
  Counter black_disks;

 public:
  void flipEvent(char current_player_sign);
  ScoreTracker(Counter white_disks, Counter black_disks);
  Counter &getWhiteDisks();
  Counter &getBlackDisks();
  void increase(char sign);
  void increase(char sign, int value);

  char getWinnerSign();
};

#endif //EX02_SCORETRACKINGLISTENER_H
