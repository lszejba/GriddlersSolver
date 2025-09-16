#include <Board.hpp>

static Board Board::getInstance()
{
    if (Board::instance == nullptr)
    {
        Board::instance = new Board();
    }
    return Board::instance;
}

Board::Board()
{
    rows = -1;
    columns = -1;
}
