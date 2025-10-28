#include <iostream>
#include "Board.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;

    Board board = Board::getInstance();

    board.LoadNewBoard("tests/5x5_3fullrows.test");
    board.PrintBaseInfo();
    board.PrintBoardContents();

    std::cout << std::endl << std::endl << std::endl;

    board.LoadNewBoard("tests/5x3_2fullrows.test");
    board.PrintBaseInfo();
    board.PrintBoardContents();

    return 0;
}
