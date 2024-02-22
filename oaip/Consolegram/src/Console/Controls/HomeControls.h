#pragma once
#include "Chats/Chat.h"
#include "Chats/ChatRepository.h"

namespace Consolegram::Console::Controls::Home
{
    Domain::Chats::Chat* SelectChat(Domain::Chats::ChatRepository& chatRepository);
}
