#pragma once
#include "GetChatMessagesResponse.h"

#include "../../../Domain/Messages/MessageRepository.h"
#include "../../../Domain/Users/UserRepository.h"
#include "../../../SharedKernel/ResultT.h"

namespace Consolegram::Application::Messages::GetChatMessages
{
    SharedKernel::ResultT<GetChatMessagesResponse> Handle(
        long chatId,
        Domain::Messages::MessageRepository& messageRepository,
        Domain::Users::UserRepository& userRepository);
}
