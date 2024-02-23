#include "GetChatMessagesResponse.h"

namespace Consolegram::Application::Messages::GetChatMessages
{
    GetChatMessagesResponse::GetChatMessagesResponse(const std::vector<Domain::Users::User>& users,
                                                     const std::vector<Domain::Messages::Message>& messages)
        : _users{users}, _messages{messages}
    {
    }

    std::vector<Domain::Users::User> GetChatMessagesResponse::GetUsers() const
    {
        return _users;
    }

    std::vector<Domain::Messages::Message> GetChatMessagesResponse::GetMessages() const
    {
        return _messages;
    }
}
