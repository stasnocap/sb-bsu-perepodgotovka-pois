#include "Message.h"

#include <sstream>

#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Messages
{
    Message::Message(const long id, const long userId, const long chatId, std::string text)
        : SharedKernel::Entity(id), _userId{userId}, _chatId{chatId}, _text{std::move(text)}
    {
    }

    long Message::GetUserId() const
    {
        return _userId;
    }

    long Message::GetChatId() const
    {
        return _chatId;
    }

    std::string_view Message::GetText() const
    {
        return _text;
    }

    std::string Message::ToFileString() const
    {
        std::ostringstream oStringStream{};
        
        oStringStream
            << GetId() << '\t'
            << GetUserId() << '\t'
            << GetChatId() << '\t'
            << GetText();
        
        return oStringStream.str();
    }
}
