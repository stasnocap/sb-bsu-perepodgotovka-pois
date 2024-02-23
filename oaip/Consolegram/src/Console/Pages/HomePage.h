#pragma once
#include "../../Domain/Users/User.h"
#include "../../Domain/Participants/ParticipantRepository.h"
#include "../../Domain/Chats/ChatRepository.h"
#include "../../Domain/Messages/MessageRepository.h"

namespace Consolegram::Console::Pages::Home
{
    bool Show(
        const Domain::Users::User* user,
        Domain::Participants::ParticipantRepository& participantRepository,
        Domain::Chats::ChatRepository& chatRepository,
        Domain::Messages::MessageRepository& messageRepository
    );
}
