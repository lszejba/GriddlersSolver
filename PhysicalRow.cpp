#include <iostream>
#include <sstream>
#include "Enums.hpp"
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
    MessageQueue& mQueue = MessageQueue::GetInstance();
    std::string name = ReceiverName();

    if (logicalGroups.size() < 1 || (logicalGroups.size() == 1 && logicalGroups[0] == 0))
    {
        groups.clear();
        return;
    }
    groups.reserve(logicalGroups.size());
    for (unsigned int i = 0; i < logicalGroups.size(); i++)
    {
        groups.push_back(std::make_shared<LogicalGroup>(i, logicalGroups[i], name));
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
    MessageQueue &mQueue = MessageQueue::GetInstance();

    std::cout << "[PhysicalRow.PROCESS] <<" << ReceiverName() << ">>" << std::endl;
    for (auto& field : contents)
    {
        std::cout << "- checking field " << field->SenderName() << std::endl;
        if (field->GetState() != FieldState::Unknown)
        {
            continue;
        }

        std::vector<std::shared_ptr<IReceiver>> receivers = mQueue.GetReceiversForSender(field);
        bool fieldInLogicalGroups = false;
        for (auto ptr : receivers)
        {
            IReceiver* rcv = ptr.get();
            for (auto groupPtr : groups)
            {
                if (groupPtr.get() == rcv)
                {
                    fieldInLogicalGroups = true;
                    break;
                }
            }
            if (fieldInLogicalGroups)
            {
                break;
            }
        }
        if (!fieldInLogicalGroups)
        {
            std::cout << "... field " << field->SenderName() << " doesn't belong to any logical group in this PhysicalRow, set to EMPTY" << std::endl;
            field->UpdateState(FieldState::Empty);
            std::cout << "&&& after field.UpdateState()" << std::endl;
        }
    }
    std::cout << "[PhysicalRow.PROCESS] done" << std::endl;
}

std::string PhysicalRow::ReceiverName()
{
    std::ostringstream oss;
    oss << ((type == PhysicalRowType::Row) ? "Row" : "Column") << " [" << this->number << "]";
    return oss.str();
}
