#ifndef LOGICALGROUP_HPP
#define LOGICALGROUP_HPP

#include <memory>
#include <vector>
#include "Field.hpp"

class LogicalGroup
{
public:
    LogicalGroup(int size);
    void Process();
private:
    int size;
    std::vector<std::shared_ptr<Field>> candidates;
    bool finished;
};

#endif
