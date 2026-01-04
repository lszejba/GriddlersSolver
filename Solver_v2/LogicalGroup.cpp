#include <iostream>
#include <sstream>
#include "LogicalGroup.hpp"

LogicalGroup::LogicalGroup(int index, int size) : index(index), size(size), finished(false)
{
}

void LogicalGroup::AddCandidate(std::shared_ptr<Field> candidate)
{
    candidates.push_back(candidate);
}

std::string LogicalGroup::ReceiverName()
{
    std::ostringstream oss;
    oss << "LogicalGroup [" << this->index << "]";
    return oss.str();
}


void LogicalGroup::Process()
{
    std::cout << "[PROCESS] <<" << ReceiverName() << ">>" << std::endl;
    // TODO: implement
}
