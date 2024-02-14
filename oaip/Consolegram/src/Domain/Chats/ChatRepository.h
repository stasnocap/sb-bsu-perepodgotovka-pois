#pragma once

#include "Chat.h"
#include "../../SharedKernel/Repository.h"
#include "../../SharedKernel/Config.h"

namespace Consolegram::Domain::Chats
{
    class ChatRepository : public SharedKernel::Repository<Chat>
    {
    public:
        explicit ChatRepository(const SharedKernel::Config& config);
    };
}