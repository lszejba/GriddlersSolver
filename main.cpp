#include <QCoreApplication>
#include <board.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Board board(10, 10);
    std::string boardStr = "4;1,1;2;3,4;2,1;2,3,1;1,2,3;1,1;1,1,1,1;4,1#6;3,1;1,1;2,1,4;1,1,1;1,2,1;2,1,1;1,2,1;1,1,1;3,1";
    if (!board.ProcessFile(boardStr)) {
        std::cout << "Data processing failed\n";
        return -1;
    }
    board.Process();
//    board.DBG_ProcessOnce();
//    board.DBG_ProcessOnce();
//    board.DBG_ProcessOnce();
//    board.DBG_ProcessOnce();

    return a.exec();
}
