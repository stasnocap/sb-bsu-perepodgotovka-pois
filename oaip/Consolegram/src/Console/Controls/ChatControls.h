#pragma once
#include "Chats/Chat.h"
#include "Messages/MessageRepository.h"
#include "Participants/ParticipantRepository.h"
#include "Users/User.h"

namespace Consolegram::Console::Controls::Chat
{
    void WriteMessage(const Domain::Users::User* user,
                      const Domain::Chats::Chat* chat,
                      Domain::Messages::MessageRepository& messageRepository,
                      Domain::Participants::ParticipantRepository& participantRepository);
}
