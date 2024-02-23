#include "GetChatMessagesHandler.h"

namespace Consolegram::Application::Messages::GetChatMessages
{
    SharedKernel::ResultT<GetChatMessagesResponse> Handle(
        const long chatId,
        Domain::Messages::MessageRepository& messageRepository,
        Domain::Users::UserRepository& userRepository)
    {
        const std::vector messages{messageRepository.GetLastChatMessages(chatId)};
        const std::vector users{userRepository.GetUsersByMessages(messages)};
        return SharedKernel::ResultT<GetChatMessagesResponse>::Success(GetChatMessagesResponse{users, messages});
    }
}
