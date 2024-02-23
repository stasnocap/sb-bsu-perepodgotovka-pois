#include "GetChatsWithLastMessagesResponse.h"

namespace Consolegram::Application::Chats::GetChatsWithLastMessages
{
    GetChatsWithLastMessagesResponse::GetChatsWithLastMessagesResponse(const std::vector<Domain::Chats::Chat>& chats,
        const std::vector<Domain::Messages::Message>& messages)  : _chats{chats}, _messages{messages}
    {
    }

    std::vector<Domain::Chats::Chat> GetChatsWithLastMessagesResponse::GetChats() const
    {
        return _chats;
    }

    std::vector<Domain::Messages::Message> GetChatsWithLastMessagesResponse::GetMessages() const
    {
        return _messages;
    }
}
