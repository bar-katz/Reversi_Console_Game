// Eden Yefet 204778294
// Bar Katz 208561357

#include "gtest/gtest.h"
#include "../include/Board.h"

TEST(BoardTest, BoardCopyTest) {
  int size = 4;
  Board original_board = Board(size);
  original_board.getCell(1, 1)->setSign(BLACK);
  Board board_copy = original_board.copy();

  for (int r = 1; r <= size; r++) {
    for (int c = 1; c <= size; c++) {
      EXPECT_EQ(original_board.getCell(r, c)->getSign(),
                board_copy.getCell(r, c)->getSign());
    }
  }

  original_board.getCell(2, 2)->setSign(BLACK);
  EXPECT_NE(original_board.getCell(2, 2)->getSign(),
            board_copy.getCell(2, 2)->getSign());
}

TEST(BoardTest, CoordinateToCellTest) {
  int size = 10;
  Board original_board = Board(size);
  original_board.getCell(7, 7)->setSign(BLACK);
  EXPECT_EQ(original_board.getCell(7, 7)->getSign(), BLACK);
  Coordinate coordinate = Coordinate(7, 7);

  Cell *cell_from_coordinate = original_board.coordinateToCell(coordinate);
  EXPECT_EQ(cell_from_coordinate->getSign(), BLACK);

  cell_from_coordinate->setSign(WHITE);
  EXPECT_EQ(original_board.getCell(7, 7)->getSign(), WHITE);
}