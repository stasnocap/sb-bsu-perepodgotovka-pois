#pragma once
#include <vector>

#include "../../../Domain/Messages/Message.h"
#include "../../../Domain/Users/User.h"

namespace Consolegram::Application::Messages::GetChatMessages
{
    class GetChatMessagesResponse
    {
        std::vector<Domain::Users::User> _users;
        std::vector<Domain::Messages::Message> _messages;

    public:
        explicit GetChatMessagesResponse(
            const std::vector<Domain::Users::User>& users,
            const std::vector<Domain::Messages::Message>& messages
        );

        [[nodiscard]] std::vector<Domain::Users::User> GetUsers() const;

        [[nodiscard]] std::vector<Domain::Messages::Message> GetMessages() const;
    };
}
