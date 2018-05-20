// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/ScoreTracker.h"

void ScoreTracker::flipEvent(char current_player_sign) {
  if (current_player_sign == WHITE) {
    white_disks.increase();
    black_disks.decrease();
  } else {
    white_disks.decrease();
    black_disks.increase();
  }
}

ScoreTracker::ScoreTracker(Counter white_disks,
                           Counter black_disks) {
  this->white_disks = white_disks;
  this->black_disks = black_disks;
}

Counter &ScoreTracker::getWhiteDisks() {
  return white_disks;
}

Counter &ScoreTracker::getBlackDisks() {
  return black_disks;
}

void ScoreTracker::increase(char sign) {
  if (sign == WHITE) {
    this->white_disks.increase();
  } else if (sign == BLACK) {
    this->black_disks.increase();
  } else {
    cout << "Unexpected flow: ScoreTracker-increase" << endl;
  }
}

void ScoreTracker::increase(char sign, int value) {
  if (sign == WHITE) {
    this->white_disks.increase(value);
  } else if (sign == BLACK) {
    this->black_disks.increase(value);
  } else {
    cout << "Unexpected flow: ScoreTracker-increase" << endl;
  }
}

char ScoreTracker::getWinnerSign() {
  if (this->white_disks.getCount() > this->black_disks.getCount()) {
    return WHITE;
  } else if (this->white_disks.getCount() < this->black_disks.getCount()) {
    return BLACK;
  } else {
    return TIE;
  }
}
