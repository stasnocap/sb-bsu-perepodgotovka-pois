#pragma once

#include <vector>

#include "../../../Domain/Chats/Chat.h"
#include "../../../Domain/Messages/Message.h"

namespace Consolegram::Application::Chats::GetChatsWithLastMessages
{
    class GetChatsWithLastMessagesResponse
    {
        std::vector<Domain::Chats::Chat> _chats;
        std::vector<Domain::Messages::Message> _messages;

    public:
        explicit GetChatsWithLastMessagesResponse(
            const std::vector<Domain::Chats::Chat>& chats,
            const std::vector<Domain::Messages::Message>& messages);

        [[nodiscard]] std::vector<Domain::Chats::Chat> GetChats() const;

        [[nodiscard]] std::vector<Domain::Messages::Message> GetMessages() const;
    };
}