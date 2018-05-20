// Eden Yefet 204778294
// Bar Katz 208561357


#include "../include/LocalVersusLocalChoice.h"

kMenuVal LocalVersusLocalChoice::execute() {
  game->startNewGame(new TwoPlayers(new LocalPlayer(), new LocalPlayer()),
                     this->board_size);
  return kPlay;
}

string LocalVersusLocalChoice::getTitle() {
  return "Play against a local friend";
}

LocalVersusLocalChoice::LocalVersusLocalChoice(Game *game, int board_size) {
    this->game = game;
    this->board_size = board_size;
}

LocalVersusLocalChoice::~LocalVersusLocalChoice() {
}
