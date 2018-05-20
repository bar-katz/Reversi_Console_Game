// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/LocalPlayer.h"

#define BAD_COORDINATE -1

void LocalPlayer::setSign(char sign) {
  this->sign = sign;
}

Coordinate LocalPlayer::playOneTurn(Board &board_copy,
                                    char *message,
                                    vector<Move> &available_moves) {
  int row, col;

  if (strcmp(message, "End") == 0) {
    return Coordinate(BAD_COORDINATE, BAD_COORDINATE);
  }
  if (!available_moves.empty()) {
    cin >> row >> col;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      return Coordinate(BAD_COORDINATE, BAD_COORDINATE);
    }

    // Writes move to server
    strcpy(message, "");
    ostringstream os;
    os << row << "," << col;
    strcpy(message, os.str().c_str());

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return Coordinate(row, col);
  }

  strcpy(message, "NoMove");
  return Coordinate(BAD_COORDINATE, BAD_COORDINATE);
}

char LocalPlayer::getSign() const {
  return this->sign;
}

LocalPlayer::LocalPlayer() {
  this->type = LOCAL;
}

void LocalPlayer::endGame() {

}
