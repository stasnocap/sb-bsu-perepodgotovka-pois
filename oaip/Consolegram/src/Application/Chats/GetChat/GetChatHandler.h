#pragma once

#include "../../../Domain/Chats/Chat.h"
#include "../../../Domain/Chats/ChatRepository.h"
#include "../../../SharedKernel/Result.h"

namespace Consolegram::Application::Chats::GetChat
{
    Result<Domain::Chats::Chat*> Handle(long id, Domain::Chats::ChatRepository& chatRepository);
}