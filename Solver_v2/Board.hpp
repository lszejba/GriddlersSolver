#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory>
#include <string>
#include <vector>
#include "Field.hpp"
#include "PhysicalRow.hpp"

class Board
{
public:
    static Board& getInstance();
    void LoadNewBoard(std::string path);
    void PrintBaseInfo();
    void PrintBoardContents();

private:
    Board();
    void Reset();
    void CreatePhysicalLayer();
    void InitializeLogicalLayer();

    int rows;
    int columns;
    std::vector<std::vector<int>> rowGroupsSizes;
    std::vector<std::vector<int>> columnGroupsSizes;
    std::vector<std::shared_ptr<Field>> fields;
    std::vector<std::shared_ptr<PhysicalRow>> physicalRows;
    std::vector<std::shared_ptr<PhysicalRow>> physicalColumns;
};

#endif
