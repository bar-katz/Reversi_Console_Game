// Eden Yefet 204778294
// Bar Katz 208561357

#include "gtest/gtest.h"
#include "../include/Board.h"
#include "../include/BoardLogic.h"

TEST(BoardLogicTest, CheckAvailableMoves) {
  int size = 3;
  Board board = Board(size);
  BoardLogic board_logic = BoardLogic();

  board.getCell(1, 1)->setSign(WHITE);
  board.getCell(1, 2)->setSign(BLACK);
  board.getCell(2, 1)->setSign(BLACK);
  board.getCell(2, 2)->setSign(BLACK);
  board.getCell(3, 2)->setSign(BLACK);

  vector<Move> available_moves = board_logic.getValidMoves(board, WHITE);
  vector<Coordinate> expected_moves;
  expected_moves.push_back(Coordinate(1, 3));
  expected_moves.push_back(Coordinate(3, 1));
  expected_moves.push_back(Coordinate(3, 3));

  // Checks if expected_moves is a subset of available_moves
  bool are_equal = true;
  for (int i = 0; i < available_moves.size(); i++) {
    int current_row = available_moves[i].getRow();
    int current_column = available_moves[i].getColumn();

    for (int k = 0; k < expected_moves.size(); k++) {
      for (int j = 0; j < available_moves.size(); j++) {
        if (expected_moves[k].getRow() == current_row && expected_moves[k]
            .getCol() == current_column) {
          are_equal = true;
          break;
        } else {
          are_equal = false;
        }
      }
    }
  }

  // Checks if subset AND if equal in size,
  // and therefore available_moves == expected_moves
  EXPECT_TRUE(available_moves.size() == expected_moves.size() && are_equal);
}

TEST(BoardLogicTest, UpdateBoardFromMove1) {
  int size = 3;
  Board board = Board(size);
  BoardLogic board_logic = BoardLogic();

  char player = WHITE;
  Cell player_move = Cell(3, 3);

  board.getCell(1, 1)->setSign(WHITE);

  board.getCell(1, 2)->setSign(BLACK);
  board.getCell(2, 1)->setSign(BLACK);
  board.getCell(2, 2)->setSign(BLACK);
  board.getCell(3, 2)->setSign(BLACK);

  board.getCell(player_move.getRow(), player_move.getColumn())->setSign(player);
  board_logic.updateBoardFromMove(board, NULL, &player_move, player);

  EXPECT_EQ(board.getCell(2, 2)->getSign(), player);
}

TEST(BoardLogicTest, UpdateBoardFromMove2) {
  int size = 5;
  Board board = Board(size);
  BoardLogic board_logic = BoardLogic();

  char player = WHITE;
  Cell player_move = Cell(4, 2);

  board.getCell(1, 4)->setSign(WHITE);
  board.getCell(2, 4)->setSign(WHITE);
  board.getCell(3, 4)->setSign(WHITE);

  board.getCell(3, 3)->setSign(BLACK);
  board.getCell(3, 5)->setSign(BLACK);

  board.getCell(player_move.getRow(), player_move.getColumn())->setSign(player);
  board_logic.updateBoardFromMove(board, NULL, &player_move, player);

  EXPECT_EQ(board.getCell(3, 3)->getSign(), player);
}

TEST(BoardLogicTest, GetOppositeSign) {
  BoardLogic board_logic = BoardLogic();

  char player = WHITE;
  char rival = board_logic.getOppositeSign(player);

  EXPECT_EQ(rival, BLACK);
}