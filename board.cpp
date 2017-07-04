#include "board.h"
#include <iostream>
#include <string>
#include <sstream>

Board::Board(unsigned width, unsigned height) : iWidth(width), iHeight(height)
{
    for (unsigned i = 0; i < height; i++)
        iRows.push_back(FieldLine(width));
    for (unsigned j = 0; j < width; j++)
        iColumns.push_back(FieldLine(height));
    iAllFields = new Field *[width * height];
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            Field *newField = new Field();
            iAllFields[j + i * width] = newField;
            iRows[i].AddField(newField, j);
            iColumns[j].AddField(newField, i);
        }
    }
}

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

// TODO: move this to constructor (remove size checks then)
bool Board::ProcessFile(std::string content)
{
    std::vector<std::string> elems;
    split(content, '#', std::back_inserter(elems));
    if (elems.size() != 2) {
        std::cout << "Error: invalid input file\n";
        return false;
    }
    std::vector<std::string> rowsElems;
    std::vector<std::string> columnsElems;
    split(elems[0], ';', std::back_inserter(rowsElems));
    split(elems[1], ';', std::back_inserter(columnsElems));
    if (rowsElems.size() != iRows.size()) {
        std::cout << "Error: invalid number of rows in input file\n";
        return false;
    }
    if (columnsElems.size() != iColumns.size()) {
        std::cout << "Error: invalid number of columns in input file\n";
        return false;
    }

    CreateFieldGroups(rowsElems, iRows, iWidth);
    CreateFieldGroups(columnsElems, iColumns, iHeight);

    PrintSelf();
    return true;
}

void Board::PrintSelf()
{
    std::cout << "Board\n";
    std::cout << "Rows:\n";
    for (unsigned i = 0; i < iRows.size(); i++) {
        iRows[i].PrintSelf(i);
    }
    std::cout << "Columns:\n";
    for (unsigned i = 0; i < iColumns.size(); i++) {
        iColumns[i].PrintSelf(i);
    }
    std::cout << "Board done\n";
}

void Board::DBG_ProcessOnce()
{
    for (int i = 0; i < iWidth; i++)
        iColumns[i].Process();
    for (int i = 0; i < iHeight; i++)
        iRows[i].Process();

    for (int i = 0; i < iHeight; i++)
        iRows[i].Print();
    std::cout << "\n\n";
}

void Board::CreateFieldGroups(std::vector<std::string> &elems, std::vector<FieldLine> &line, unsigned lineSize)
{
    int idx = 0;
    for (auto it = elems.begin(); it != elems.end(); it++) {
        std::vector<std::string> columnDetails;
        split(*it, ',', std::back_inserter(columnDetails));
        int frontGroupOffset = 0;
        int groupIdx = 0;
        for (auto it2 = columnDetails.begin(); it2 != columnDetails.end(); it2++) {
            // TODO
            int groupSize = -1;
            if ((*it2).length() == 0)
                groupSize = 0;
            else
                groupSize = std::stoi(*it2);
            std::cout << groupSize << " ";
            line[idx].AddFieldGroup(FieldGroup(groupSize));
            line[idx].GetFieldGroup(groupIdx)->SetLowerLimit(frontGroupOffset);
            frontGroupOffset += (line[idx].GetFieldGroup(groupIdx)->Size() + 1);
            groupIdx++;
        }
        groupIdx--;
        int backGroupOffset = lineSize - 1;
        for (; groupIdx >= 0; groupIdx--) {
            line[idx].GetFieldGroup(groupIdx)->SetUpperLimit(backGroupOffset);
            backGroupOffset -= (line[idx].GetFieldGroup(groupIdx)->Size() + 1);
        }
        std::cout << std::endl;
        idx++;
    }
}
