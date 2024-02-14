#include "Message.h"
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Messages
{
    Message::Message(const long id, const long userId, const long chatId, std::string text)
        : SharedKernel::Entity(id), _userId{userId}, _chatId{chatId}, _text{std::move(text)}
    {
    }

    [[nodiscard]] long Message::GetUserId() const
    {
        return _userId;
    }

    [[nodiscard]] long Message::GetChatId() const
    {
        return _chatId;
    }

    [[nodiscard]] std::string_view Message::GetText() const
    {
        return _text;
    }
}
