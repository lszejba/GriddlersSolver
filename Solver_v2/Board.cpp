#include "Board.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

Board& Board::getInstance()
{
    static Board instance;

    return instance;
}

void Board::LoadNewBoard(std::string path)
{
    Reset();

    std::ifstream in(path);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open board file: " + path);
    }

    // Read width and height (skip blank lines if any)
    int width = 0, height = 0;
    // read first non-empty token as width
    if (!(in >> width))
    {
        throw std::runtime_error("Failed to read width from file: " + path);
    }

    if (!(in >> height))
    {
        throw std::runtime_error("Failed to read height from file: " + path);
    }

    columns = width;
    rows = height;

    // consume the rest of the current line after reading height
    std::string line;
    std::getline(in, line);

    // Read row groups: expect one line per row (skip blank lines)
    rowGroupsSizes.reserve(rows);
    for (int r = 0; r < rows; ++r)
    {
        // get next non-empty line
        do
        {
            if (!std::getline(in, line))
            {
                throw std::runtime_error("Unexpected end of file while reading row groups");
            }
        } while (line.find_first_not_of(" \t\r\n") == std::string::npos);

        std::istringstream iss(line);
        std::vector<int> groups;
        int val;
        while (iss >> val)
        {
            groups.push_back(val);
        }
        rowGroupsSizes.push_back(std::move(groups));
    }

    // Read column groups: expect one line per column (skip blank lines)
    columnGroupsSizes.reserve(columns);
    for (int c = 0; c < columns; ++c)
    {
        // get next non-empty line
        do
        {
            if (!std::getline(in, line))
            {
                throw std::runtime_error("Unexpected end of file while reading column groups");
            }
        } while (line.find_first_not_of(" \t\r\n") == std::string::npos);

        std::istringstream iss(line);
        std::vector<int> groups;
        int val;
        while (iss >> val)
        {
            groups.push_back(val);
        }
        columnGroupsSizes.push_back(std::move(groups));
    }

    // TODO: add board validation here
    CreatePhysicalLayer();
    InitializeLogicalLayer();
}

void Board::PrintBaseInfo()
{
    std::cout << "Board (" << rows << " x " << columns << ")" << std::endl;
    std::cout << std::endl << "Rows:" << std::endl;
    for (auto row : rowGroupsSizes)
    {
        for (int size : row)
        {
            std::cout << size << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "Columns:" << std::endl;
    for (auto col : columnGroupsSizes)
    {
        for (int size : col)
        {
            std::cout << size << " ";
        }
        std::cout << std::endl;
    }
}

void Board::PrintBoardContents()
{
    if (rows < 0)
    {
        std::cout << "<BOARD EMPTY>" << std::endl;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            fields[i * columns + j]->Print();
        }
        std::cout << std::endl;
    }
}

bool Board::ProcessBoard()
{
    while (processingQueue.size() > 0)
    {
        std::shared_ptr<PhysicalRow> currentRow = processingQueue.front();
        currentRow->Process();
        processingQueue.pop();
    }
    return false;
}

// --- PRIVATE ---

Board::Board()
{
    rows = -1;
    columns = -1;
}

void Board::Reset()
{
    rows = -1;
    columns = -1;
    if (rowGroupsSizes.size() > 0)
    {
        for(auto row : rowGroupsSizes)
        {
            row.clear();
        }
        rowGroupsSizes.clear();
    }
    if (columnGroupsSizes.size() > 0)
    {
        for (auto col : columnGroupsSizes)
        {
            col.clear();
        }
        columnGroupsSizes.clear();
    }
    fields.clear();
}

void Board::CreatePhysicalLayer()
{
    if (rows <= 0 || columns <= 0)
    {
        return;
    }

    fields.reserve(rows * columns);
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            fields[y + x * columns] = std::make_shared<Field>(x, y);
        }
    }
    physicalRows.reserve(rows);
    for (int i = 0; i < rows; i++)
    {
        physicalRows[i] = std::make_shared<PhysicalRow>(i, PhysicalRowType::Row, columns);
        for (int j = 0; j < columns; j++)
        {
            physicalRows[i]->SetField(j, fields[i * columns + j]);
        }
        physicalRows[i]->CreateLogicalGroups(rowGroupsSizes[i]);
    }
    physicalColumns.reserve(columns);
    for (int j = 0; j < columns; j++)
    {
        physicalColumns[j] = std::make_shared<PhysicalRow>(j, PhysicalRowType::Column, rows);
        for (int i = 0; i < rows; i++)
        {
            physicalColumns[j]->SetField(i, fields[i * columns + j]);
        }
        physicalColumns[j]->CreateLogicalGroups(columnGroupsSizes[j]);
    }
}

void Board::InitializeLogicalLayer()
{
}
