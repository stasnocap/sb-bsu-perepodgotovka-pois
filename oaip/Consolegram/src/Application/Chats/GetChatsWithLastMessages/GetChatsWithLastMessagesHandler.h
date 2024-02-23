#pragma once
#include "GetChatsWithLastMessagesResponse.h"
#include "../../../SharedKernel/Result.h"
#include "../../../Domain/Chats/ChatRepository.h"
#include "../../../Domain/Participants/ParticipantRepository.h"
#include "../../../Domain/Messages/MessageRepository.h"

namespace Consolegram::Application::Chats::GetChatsWithLastMessages
{
    Result<GetChatsWithLastMessagesResponse> Handle(
        long userId,
        Domain::Participants::ParticipantRepository& participantRepository,
        Domain::Chats::ChatRepository& chatRepository,
        Domain::Messages::MessageRepository& messageRepository
    );
}
