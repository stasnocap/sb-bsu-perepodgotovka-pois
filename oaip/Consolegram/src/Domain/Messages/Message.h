#pragma once
#include <string_view>
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Messages
{
    class Message : public SharedKernel::Entity
    {
        long _userId{};
        long _chatId{};
        std::string _text{};

    public:
        explicit Message(long id, long userId, long chatId, std::string text);

        [[nodiscard]] long GetUserId() const;

        [[nodiscard]] long GetChatId() const;

        [[nodiscard]] std::string_view GetText() const;
    };
}
