#ifndef LOGICALGROUP_HPP
#define LOGICALGROUP_HPP

#include <memory>
#include <vector>
#include "Field.hpp"
#include "IReceiver.hpp"

// TODO: Check if doesn't have to inherit from ISender as well (or only from it)
class LogicalGroup : public IReceiver, public std::enable_shared_from_this<LogicalGroup>
{
public:
    LogicalGroup(int index, int size, std::string parentName);
    void AddCandidate(std::shared_ptr<Field> candidate);
    void Process() override;
    std::string ReceiverName() override;
private:
    int index;
    int size;
    std::string parentName;
    std::vector<std::shared_ptr<Field>> candidates;
    bool finished;
};

#endif
