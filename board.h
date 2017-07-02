#ifndef BOARD_H
#define BOARD_H

#include <fieldline.h>
#include <field.h>
#include <vector>
#include <string>

class Board
{
public:
    Board(unsigned width, unsigned height);
    bool ProcessFile(std::string content);
    void PrintSelf();
    void DBG_ProcessOnce();
private:
    void CreateFieldGroups(std::vector<std::string> &elems, std::vector<FieldLine> &line, unsigned lineSize);
    std::vector<FieldLine> iRows;
    std::vector<FieldLine> iColumns;
    Field **iAllFields;
    unsigned iWidth;
    unsigned iHeight;
};

#endif // BOARD_H
