#include <iostream>
#include <sstream>
#include "LogicalGroup.hpp"

LogicalGroup::LogicalGroup(int index, int size, std::string parentName)
    : index(index), size(size), parentName(parentName), finished(false)
{
}

void LogicalGroup::AddCandidate(std::shared_ptr<Field> candidate)
{
    candidates.push_back(candidate);
}

std::string LogicalGroup::ReceiverName()
{
    std::ostringstream oss;
    oss << "[Logic] " << parentName << " [[" << this->index << "]] (size: " << size << ")";
    return oss.str();
}


void LogicalGroup::Process()
{
    std::cout << "[PROCESS] <<" << ReceiverName() << ">>" << std::endl;
    // TODO: implement
}
