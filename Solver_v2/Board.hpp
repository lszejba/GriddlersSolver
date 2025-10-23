#ifndef BOARD_HPP
#define BOARD_HPP

class Board
{
public:
    static Board& getInstance();
    void LoadNewBoard(/*params*/);

private:
    Board();
    void Reset();

    //static Board instance;
    int rows;
    int columns;
};

#endif
