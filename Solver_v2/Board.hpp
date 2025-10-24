#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>

class Board
{
public:
    static Board& getInstance();
    void LoadNewBoard(std::string path);
    void PrintBaseInfo();

private:
    Board();
    void Reset();

    int rows;
    int columns;
    std::vector<std::vector<int>> rowGroupsSizes;
    std::vector<std::vector<int>> columnGroupsSizes;
};

#endif
