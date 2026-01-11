#include <iostream>
#include <sstream>
#include "LogicalGroup.hpp"
#include "MessageQueue.hpp"

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
    std::cout << "[LogicalGroup.PROCESS] <<" << ReceiverName() << ">>" << std::endl;
    if (finished)
    {
        return;
    }

    MessageQueue &mQueue = MessageQueue::GetInstance();
    std::shared_ptr<LogicalGroup> thisPtr = shared_from_this();
    // **** if any EMPTY Field is present - update range for any bordering part that is too small to contain whole group
    // 1. set all fields with Empty state to nullptr
    for(uint i = 0; i < candidates.size(); i++)
    {
        if (candidates[i] == nullptr)
        {
            continue;
        }
        if (candidates[i].get()->GetState() == FieldState::Empty)
        {
            std::cout << "... Removing Empty field " << candidates[i].get()->SenderName() << std::endl;
            candidates[i] = nullptr;
        }
    }
    // 2. go through whole vector, clear each separate subgroup that is too small to contain whole group
    int currentStart = -1;
    int currentEnd = -1;
    for (uint i = 0; i < candidates.size(); i++)
    {
        if (candidates[i] == nullptr)
        {
            if (currentStart != -1)
            {
                if (currentEnd - currentStart + 1 < size)
                {
                    std::cout << "... Existing subgroup too short to contain whole group, removing fields from "
                        << candidates[currentStart].get()->SenderName()
                        << " to " << candidates[currentEnd].get()->SenderName() << " ..." << std::endl;
                }
                for (int j = currentStart; j <= currentEnd; j++)
                {
                    mQueue.AddMessage(std::make_shared<Message>(candidates[j], thisPtr, MessageType::Unregister));
                    candidates[j] = nullptr;
                }
                currentStart = -1;
                currentEnd = -1;
            }
        }
        else
        {
            if (currentStart == -1)
            {
                currentStart = i;
            }
            currentEnd = i;
        }
    }
    // 3. Remove all leading and trailing nullptr
    for (auto it = candidates.begin(); it != candidates.end(); )
    {
        if (*it == nullptr)
        {
            std::cout << "... Removing leading empty candidate" << std::endl;
            it = candidates.erase(it);
        }
        else
        {
            break;
        }
    }
    while (!candidates.empty() && candidates.back() == nullptr)
    {
        std::cout << "... Removing trailing empty candidate" << std::endl;
        candidates.pop_back();
    }

    // **** check if intersection exists (when whole group starting from the first field and from the last share Fields)
    // ***** when it does - set every field to FULL [generate Event for each updated Field]
    // **** check if multiple groups of FULL Fields exist in LogicalGroup
    // ***** if any group is longer than expected - validate if previous OR next LogicalGroup can contain it (if both, TBD)
    // ****** if only previous OR next LogicalGroup can be owner - update range accordingly (include additional field as potential EMPTY separator)
    // ***** if multiple groups are only registered to this LogicalGroup - validate if they can be connected  (resulting group should be shorter/equal to expected size)
    // ****** if TRUE - set all Fields in between to FULL [generate Events]
    // ****** if FALSE - something went wrong [generate error Event, stop processing]
    // **** check if only one continuous group of FULL Fields exists - if size is equal to expected: add EMPTY separators if needed [generate Events], update range, mark LogicalGroup as FINISHED [generate Event]
}
