#include "Board.hpp"

Board& Board::getInstance()
{
    static Board instance;

    return instance;
    /*if (Board::instance == nullptr)
    {
        Board::instance = new Board();
    }
    return Board::instance;*/
}

Board::Board()
{
    rows = -1;
    columns = -1;
}
