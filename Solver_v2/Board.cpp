#include "Board.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

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
    std::vector<std::vector<int>> rowGroups;
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
    //std::vector<std::vector<int>> columnGroups;
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
}
