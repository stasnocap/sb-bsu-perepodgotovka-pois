#pragma once
#include "GetChatMessagesResponse.h"

#include "../../../Domain/Messages/MessageRepository.h"
#include "../../../Domain/Users/UserRepository.h"
#include "../../../SharedKernel/Result.h"

namespace Consolegram::Application::Messages::GetChatMessages
{
    Result<GetChatMessagesResponse> Handle(
        long chatId,
        Domain::Messages::MessageRepository& messageRepository,
        Domain::Users::UserRepository& userRepository);
}
