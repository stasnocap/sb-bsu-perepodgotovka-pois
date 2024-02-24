#pragma once
#include "Chats/ChatRepository.h"
#include "Messages/MessageRepository.h"
#include "Users/UserRepository.h"

namespace Consolegram::Console::Pages::Chat
{
    bool Show(
        const Domain::Chats::Chat* chat,
        Domain::Messages::MessageRepository& messageRepository,
        Domain::Users::UserRepository& userRepository);
}
