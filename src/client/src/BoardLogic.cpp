// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/BoardLogic.h"

BoardLogic::BoardLogic() {}

vector<Move> BoardLogic::getValidMoves(Board &board, char current_player) {

  int board_size = board.getSize();
  vector<Move> available_moves;
  vector<Cell *> dummy_vector;

  for (int r = 1; r <= board_size; r++) {
    for (int c = 1; c <= board_size; c++) {
      if (board.getCell(r, c)->getSign() == current_player) {
        vector<Move> sub_vector;
        searchAround(board, r, c, sub_vector, dummy_vector);

        // checks for duplicates while merging the two vectors
        mergeVectorsWithoutDuplicates(sub_vector, available_moves);
      }
    }
  }
  return available_moves;
}

int BoardLogic::updateBoardFromMove(Board &board,
                                    ScoreTracker *score_tracker,
                                    Cell *player_move,
                                    char player) {
  int row = player_move->getRow();
  int col = player_move->getColumn();
  vector<Cell *> rival_disks_to_flip;
  vector<Move> dummy_moves_vector;

  player_move->setSign(player);
  if (score_tracker != NULL) {
    score_tracker->increase(player);
  }

  this->searchAround(board, row, col, dummy_moves_vector, rival_disks_to_flip);

  for (int i = 0; i < rival_disks_to_flip.size(); i++) {
    rival_disks_to_flip[i]->setSign(player);
    if (score_tracker != NULL) {
      score_tracker->flipEvent(player);
    }
  }

  return int(rival_disks_to_flip.size());
}

void BoardLogic::searchAround(Board &board,
                              int row,
                              int col,
                              vector<Move> &available_moves,
                              vector<Cell *> &disks_to_flip) {
  // Checks each direction
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      if (dy == 0 && dx == 0) {
        continue;
      }
      searchOneDirection(dy,
                         dx,
                         board,
                         available_moves,
                         board.getCell(row, col),
                         disks_to_flip);
    }
  }
}

void BoardLogic::searchOneDirection(int dy,
                                    int dx,
                                    Board &board,
                                    vector<Move> &available_moves,
                                    Cell *original_cell,
                                    vector<Cell *> &disks_to_flip) {

  int row = original_cell->getRow();
  int column = original_cell->getColumn();
  int board_size = board.getSize();
  char original_sign = original_cell->getSign();
  bool opposite_player_found = false;
  int move_score = 0;
  vector<Cell *> temp_disks_to_flip;

  while (true) {
    // Moves one step in direction
    row += dy;
    column += dx;

    // Checks board bounds
    if (row < 1 || column < 1 || row > board_size || column > board_size) {
      return;
    }

    Cell *current_cell = board.getCell(row, column);
    if (current_cell->getSign() == getOppositeSign(original_sign)) {
      opposite_player_found = true;
      temp_disks_to_flip.push_back(current_cell);
      move_score++;
    } else if (current_cell->getSign() == original_sign) {
      // Merge temp_disks_to_flip to disks_to_flip
      for (int i = 0; i < temp_disks_to_flip.size(); i++) {
        for (int j = 0; j < disks_to_flip.size(); j++) {
          if (temp_disks_to_flip[i]->isEqual(*disks_to_flip[j])) {
            continue;
          }
        }
        disks_to_flip.push_back(temp_disks_to_flip[i]);
      }
      return;
    } else if (current_cell->getSign() == EMPTY && opposite_player_found) {
      // Check for duplication
      for (int i = 0; i < available_moves.size(); i++) {
        if (board.coordinateToCell(available_moves[i].getCoordinate()) ==
            current_cell) {
          return;
        }
      }
      available_moves.push_back(Move(Coordinate(row, column), move_score));
      return;
    } else if (current_cell->getSign() == EMPTY && !opposite_player_found) {
      return;
    }
  }
}

char BoardLogic::getOppositeSign(char player_sign) {
  if (player_sign == WHITE) {
    return BLACK;
  } else if (player_sign == BLACK) {
    return WHITE;
  } else {
    cout << "getOppositeSign-bad-workflow-returns-EMPTY" << endl;
    return EMPTY;
  }
}

void BoardLogic::mergeVectorsWithoutDuplicates(vector<Move> &v1,
                                               vector<Move> &v2) {
  bool is_duplicate;
  for (int i = 0; i < v1.size(); i++) {
    is_duplicate = false;
    for (int j = 0; j < v2.size(); j++) {
      if (v1[i].getCoordinate().isEqual(v2[j].getCoordinate())) {
        is_duplicate = true;
      }
    }

    if (!is_duplicate) {
      v2.push_back(v1[i]);
    }
  }
}
