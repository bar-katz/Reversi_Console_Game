// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/AIPlayer.h"

Coordinate AIPlayer::playOneTurn(Board &board_copy,
                                 char *message,
                                 vector<Move> &available_moves) {
  float opponent_min_score = INFINITY;
  int best_row = -1;
  int best_col = -1;

  // Implements Minimax algorithm to find the move that will lead to the
  // minimum possible profit for the opponent on its upcoming turn.
  for (int i = 0; i < available_moves.size(); i++) {
    Board board_copy_of_copy = board_copy.copy();
    Cell *current_move = board_copy_of_copy.coordinateToCell
        (available_moves[i].getCoordinate());
    int opponent_current_max = simulateMove(current_move, board_copy_of_copy);

    // Picks the minimum of the maximums ("lowest upper bound")
    if (opponent_current_max < opponent_min_score) {
      opponent_min_score = opponent_current_max;
      best_row = current_move->getRow();
      best_col = current_move->getColumn();
    }
  }

  return Coordinate(best_row, best_col);
}

void AIPlayer::setSign(char sign) {
  this->sign = sign;
}

char AIPlayer::getSign() const {
  return this->sign;
}

int AIPlayer::simulateMove(Cell *choice, Board &current_board) {
  int max_possible_score = -1;

  // Makes a move on the board copy
  this->board_logic.updateBoardFromMove(current_board,
                                        NULL,
                                        choice,
                                        this->sign);

  // Checks potential opponent moves scores
  vector<Move> opponent_available_moves = board_logic.getValidMoves
      (current_board, board_logic.getOppositeSign(this->sign));

  // Returns maximum possible score for the opponent
  for (int i = 0; i < opponent_available_moves.size(); i++) {
    Move *current_move = &opponent_available_moves[i];
    if (current_move->getScore() > max_possible_score) {
      max_possible_score = current_move->getScore();
    }
  }
  return max_possible_score;
}

AIPlayer::AIPlayer() {
  this->type = AI;
}

void AIPlayer::endGame() {

}
