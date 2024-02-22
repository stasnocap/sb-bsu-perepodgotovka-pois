#pragma once
#include <vector>

#include "Message.h"
#include "../../SharedKernel/Repository.h"
#include "../../SharedKernel/Config.h"

namespace Consolegram::Domain::Messages
{
    class MessageRepository : public SharedKernel::Repository<Message>
    {
    public:
        explicit MessageRepository(const SharedKernel::Config& config);

        std::vector<Message> GetLastMessages(std::vector<long>& chatIds);

        std::vector<Message> GetLastChatMessages(long chatId);
    };
}
