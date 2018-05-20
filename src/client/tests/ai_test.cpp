// Eden Yefet 204778294
// Bar Katz 208561357

#include "gtest/gtest.h"
#include "../include/AIPlayer.h"

TEST(AITest, CheckChoice1) {
  int size = 3;
  Board board = Board(size);
  BoardLogic board_logic = BoardLogic();
  vector<Move> available_moves;
  AIPlayer ai = AIPlayer();
  char message[7] = "";
  ai.setSign(WHITE);

  board.getCell(1, 1)->setSign(WHITE);

  board.getCell(1, 2)->setSign(BLACK);
  board.getCell(2, 1)->setSign(BLACK);
  board.getCell(2, 2)->setSign(BLACK);
  board.getCell(3, 2)->setSign(BLACK);

  available_moves = board_logic.getValidMoves(board, WHITE);
  Board board_copy = board.copy();
  Coordinate move =
      ai.playOneTurn(board_copy, message, available_moves);

  EXPECT_FALSE(move.getRow() == 3 && move.getCol() == 1);
}

TEST(AITest, CheckChoice2) {
  int size = 5;
  Board board = Board(size);
  BoardLogic board_logic = BoardLogic();
  vector<Move> available_moves;
  AIPlayer ai = AIPlayer();
  char message[7] = "";
  ai.setSign(WHITE);

  board.getCell(1, 4)->setSign(WHITE);
  board.getCell(2, 4)->setSign(WHITE);
  board.getCell(3, 4)->setSign(WHITE);

  board.getCell(3, 3)->setSign(BLACK);
  board.getCell(3, 5)->setSign(BLACK);

  available_moves = board_logic.getValidMoves(board, WHITE);

  Board board_copy = board.copy();
  Coordinate move =
      ai.playOneTurn(board_copy, message, available_moves);

  EXPECT_TRUE(move.getRow() == 4 && move.getCol() == 2);
}