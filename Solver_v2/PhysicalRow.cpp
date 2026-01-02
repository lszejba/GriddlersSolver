#include <iostream>
#include <sstream>
#include "MessageQueue.hpp"
#include "PhysicalRow.hpp"

PhysicalRow::PhysicalRow(int n, PhysicalRowType type, int size) : number(n), type(type)
{
    contents.reserve(size);
}

// TODO: think about renaming at some point
void PhysicalRow::SetField(std::shared_ptr<Field> field)
{
    contents.push_back(field);
}

void PhysicalRow::CreateLogicalGroups(std::vector<int>& logicalGroups)
{
    MessageQueue mQueue = MessageQueue::GetInstance();

    if (logicalGroups.size() < 1 || (logicalGroups.size() == 1 && logicalGroups[0] == 0))
    {
        groups.clear();
    }
    groups.reserve(logicalGroups.size());
    for (unsigned int i = 0; i < logicalGroups.size(); i++)
    {
        groups.push_back(std::make_shared<LogicalGroup>(i, logicalGroups[i]));
    }

    for (unsigned int i = 0; i < groups.size(); i++)
    {
        int startIdx = 0;//-1;
        int endIdx = contents.size() - 1;

        if (i != 0)
        {
            startIdx += i;
            for (unsigned int j = 0; j < i; j++)
            {
                startIdx += logicalGroups[j];
            }
        }

        if (i != groups.size() - 1)
        {
            endIdx -= /*contents.size() - 1 - */ (logicalGroups.size() - 1 - i);
            for (unsigned int j = logicalGroups.size() - 1; j > i; j--)
            {
                endIdx -= logicalGroups[j];
            }
        }

        for (int k = startIdx; k <= endIdx; k++)
        {
            groups[i]->AddCandidate(contents[k]);
            mQueue.AddMessage(std::make_shared<Message>(contents[k], groups[i], MessageType::Register));
        }
    }
}

void PhysicalRow::Process()
{

}

std::string PhysicalRow::ReceiverName()
{
    std::ostringstream oss;
    oss << "PhysicalRow (" << ((type == PhysicalRowType::Row) ? "Row" : "Column") << ") [" << this->number << "]";
    return oss.str();
}
