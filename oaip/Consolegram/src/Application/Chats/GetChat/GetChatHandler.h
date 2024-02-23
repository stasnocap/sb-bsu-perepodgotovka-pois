#pragma once

#include "../../../Domain/Chats/Chat.h"
#include "../../../Domain/Chats/ChatRepository.h"
#include "../../../SharedKernel/ResultT.h"

namespace Consolegram::Application::Chats::GetChat
{
    SharedKernel::ResultT<Domain::Chats::Chat*> Handle(long id, Domain::Chats::ChatRepository& chatRepository);
}