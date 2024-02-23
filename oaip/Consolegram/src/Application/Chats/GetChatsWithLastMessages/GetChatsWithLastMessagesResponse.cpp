#include "GetChatsWithLastMessagesResponse.h"

namespace Consolegram::Application::Chats::GetChatsWithLastMessages
{
    std::vector<Domain::Chats::Chat> GetChatsWithLastMessagesResponse::GetChats() const
    {
        return _chats;
    }

    std::vector<Domain::Messages::Message> GetChatsWithLastMessagesResponse::GetMessages() const
    {
        return _messages;
    }
}
