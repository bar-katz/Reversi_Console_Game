// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/Game.h"

Game::Game(Display *display) {
  this->display = display;
}

// Initiates a new game. This function returns when the game is over and the
// result of the game is announced, by one of the players winning or by a tie.
void Game::startNewGame(TwoPlayers *twoPlayers, int board_size) {
  initializeGame(twoPlayers, board_size);

  this->display->print(cout << "\n*** New Game Session ***" << endl);
  // plays turns while keeping track of no-moves situations. If both players
  // have no available moves the game ends.
  int no_moves_counter = 0;
  while (no_moves_counter < 2) {
    if (!game_logic->playOneTurn()) {
      no_moves_counter++;
    } else {
      no_moves_counter = 0;
    }
  }
  this->game_logic->getCurrentPlayer()->endGame();

  // announces winner
  char winner = this->game_logic->getScoreTracker()->getWinnerSign();
  this->display->print(cout << endl << "***Game Over***" << endl);
  if (winner == WHITE) {
    this->display->print(cout << "WHITE player won!" << endl);
  } else if (winner == BLACK) {
    this->display->print(cout << "BLACK player won!" << endl);
  } else {
    this->display->print(cout << "It's a tie! Everybody wins!" << endl);
  }

  delete twoPlayers;
  resetGame();
}

void Game::initializeGame(TwoPlayers *twoPlayers, int board_size) {
  this->board = new Board(board_size);
  Counter white_disks = Counter();
  Counter black_disks = Counter();
  this->score_tracking_listener = new ScoreTracker(white_disks, black_disks);
  this->two_players = twoPlayers;
  this->game_logic =
      new GameLogic(board,
                    two_players->getP2(),
                    two_players->getP1(),
                    score_tracking_listener,
                    display);
}

void Game::resetGame() {
  if (this->game_logic != NULL) {
    delete game_logic;
  }
  if (this->score_tracking_listener != NULL) {
    delete score_tracking_listener;
  }
  if (this->board != NULL) {
    delete board;
  }
}
