#include <iostream>
#include "Board.hpp"

int main(int argc, char **argv) {
    if (argc < 2)
    {
        std::cout << "Please provide path to board" << std::endl;
        return -1;
    }

    Board board = Board::getInstance();

    board.LoadNewBoard(argv[1]);
    board.PrintBaseInfo();
    board.PrintBoardContents();

    board.ProcessBoard();
    std::cout << std::endl << std::endl;
    board.PrintBoardContents();

    return 0;
}
