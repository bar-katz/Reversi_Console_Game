//
// Created by Eden Yefet
//


#include "../include/LocalVersusAIChoice.h"

kMenuVal LocalVersusAIChoice::execute() {
  game->startNewGame(new TwoPlayers(new LocalPlayer(), new AIPlayer()),
                     this->board_size);
  return kPlay;
}

string LocalVersusAIChoice::getTitle() {
  return "Play against an AI";
}

LocalVersusAIChoice::~LocalVersusAIChoice() {

}

LocalVersusAIChoice::LocalVersusAIChoice(Game *game, int board_size) {
  this->game = game;
  this->board_size = board_size;
}
