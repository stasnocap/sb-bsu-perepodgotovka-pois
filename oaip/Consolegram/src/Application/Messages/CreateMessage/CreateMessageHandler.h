#pragma once

#include "../../../Domain/Messages/MessageRepository.h"
#include "../../../SharedKernel/ResultT.h"

namespace Consolegram::Application::Messages::CreateMessage
{
    SharedKernel::Result Handle(long userId, long chatId, std::string_view messageText,
                                Domain::Messages::MessageRepository& messageRepository);
}
