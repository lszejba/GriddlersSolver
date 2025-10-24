#include <iostream>
#include "Board.hpp"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;

    Board board = Board::getInstance();

    board.LoadNewBoard("tests/5x5_3fullrows.test");
    board.PrintBaseInfo();

    return 0;
}
