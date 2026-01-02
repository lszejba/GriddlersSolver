#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory>
#include <queue>
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
    bool ProcessBoard();

private:
    Board();
    void Reset();
    void CreatePhysicalLayer();

    int rows;
    int columns;
    std::vector<std::vector<int>> rowGroupsSizes;
    std::vector<std::vector<int>> columnGroupsSizes;
    std::vector<std::shared_ptr<Field>> fields;
    std::vector<std::shared_ptr<PhysicalRow>> physicalRows;
    std::vector<std::shared_ptr<PhysicalRow>> physicalColumns;
    std::queue<std::shared_ptr<PhysicalRow>> processingQueue;
};

#endif
