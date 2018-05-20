// Eden Yefet 204778294
// Bar Katz 208561357

#include <cstdlib>
#include "../include/GameLogic.h"

GameLogic::GameLogic(Board *game_board,
                     Player *p1,
                     Player *p2,
                     ScoreTracker *score_tracker,
                     Display
                     *display) : board_logic() {

  strcpy(message, "");
  this->display = display;
  this->game_board = game_board;
  this->p1 = p1;
  if (p1->getSign() != BLACK && p1->getSign() != WHITE) {
    this->p1->setSign(WHITE);
  }

  this->p2 = p2;
  if (p1->getSign() == WHITE) {
    this->p2->setSign(BLACK);
    this->current_player = p2;
  } else {
    this->p2->setSign(WHITE);
    this->current_player = p1;
  }

  this->score_tracker = score_tracker;

  // Initializes starting points
  int size = game_board->getSize();
  this->game_board->getCell(size / 2 + 1, (size - 1) / 2 + 1)->setSign(BLACK);
  this->game_board->getCell((size - 1) / 2 + 1, size / 2 + 1)->setSign(BLACK);
  this->score_tracker->increase(BLACK, 2);

  this->game_board->getCell(size / 2, size / 2)->setSign(WHITE);
  this->game_board->getCell(size / 2 + 1, size / 2 + 1)->setSign(WHITE);
  this->score_tracker->increase(WHITE, 2);
}

bool GameLogic::playOneTurn() {
  // Creates a vector of available moves
  vector<Move> available_moves =
      this->board_logic.getValidMoves(*game_board,
                                      this->current_player->getSign());

  // Prints current score
  this->display->print(cout << endl << "Whites: "
                            << this->score_tracker->getWhiteDisks().getCount()
                            << ", Blacks: " <<
                            this->score_tracker->getBlackDisks().getCount()
                            << endl);

  // Creates and prints a board copy with visual '*'s as available moves
  Board board_with_moves = this->game_board->getBoardWithMoves(available_moves);
  this->display->printBoard(&board_with_moves);
  if (this->current_player->getType() == LOCAL) {
    this->display->print(
        cout << getNameFromChar(this->current_player->getSign())
             << ", It's your turn." << endl);

    if (!available_moves.empty()) {
      // Prints available moves
      this->display->print(
          cout
              << "Please enter one of the following moves, space-separated (\"r "
                  "c\"):" << endl);

      for (int i = 0; i < available_moves.size(); i++) {
        Cell *current_cell = this->game_board->coordinateToCell
            (available_moves[i].getCoordinate());
        this->display->print(cout << "(" << current_cell->getRow() << ", "
                                  << current_cell->getColumn() << ") ");
      }
      this->display->print(cout << endl);
    }
  }


  // Asks current player to make a move
  Board board_copy = this->game_board->copy();
  Coordinate chosen_cell_coordinate(-1, -1);
  try {
    chosen_cell_coordinate =
        this->current_player->playOneTurn(board_copy,
                                          this->message,
                                          available_moves);
  } catch (exception &e) {
    e.what();
    exit(1);
  }


  // No moves
  if (available_moves.empty()) {

    this->display->print(cout << "No available moves. Turn moves to " <<
                              this->board_logic.getOppositeSign(this->current_player->getSign())
                              << " player" << endl);
    this->switchTurn();
    return false;

  } else {

    Cell *chosen_cell =
        this->game_board->coordinateToCell(chosen_cell_coordinate);

    // Validates move
    while (!isValidMove(available_moves, chosen_cell)) {
      this->display->print(
          cout << "Invalid move. Please enter a valid move!" << endl);
      chosen_cell_coordinate =
          this->current_player->playOneTurn(board_copy,
                                            this->message,
                                            available_moves);
      chosen_cell = this->game_board->coordinateToCell(chosen_cell_coordinate);
    }

    // Updates board according to move, and prints the chosen move.
    this->board_logic.updateBoardFromMove(*game_board,
                                          this->score_tracker,
                                          chosen_cell,
                                          this->current_player->getSign());

    this->display->print(
        cout << "Player " << getNameFromChar(this->current_player->getSign())
             << " chose (" << chosen_cell->getRow() << ", "
             << chosen_cell->getColumn() << ")." << endl);

    this->switchTurn();
    return true;
  }
}

void GameLogic::switchTurn() {
  if (this->p1 == this->current_player) {
    this->current_player = this->p2;
  } else {
    this->current_player = this->p1;
  }
}

ScoreTracker *GameLogic::getScoreTracker() const {
  return this->score_tracker;
}

bool GameLogic::isValidMove(vector<Move> available_moves, Cell *move) {
  if (move == NULL) {
    return false;
  }

  for (int i = 0; i < available_moves.size(); i++) {
    if (available_moves[i].getColumn() == move->getColumn() &&
        available_moves[i].getRow() == move->getRow()) {
      return true;
    }
  }
  return false;
}

string GameLogic::getNameFromChar(char player_sign) {
  if (player_sign == WHITE) {
    return "WHITE [O]";
  } else if (player_sign == BLACK) {
    return "BLACK [X]";
  } else {
    return "Unexpected flow: LocalPlayer-getName()";
  }
}

Player *GameLogic::getCurrentPlayer() {
  return this->current_player;
}
