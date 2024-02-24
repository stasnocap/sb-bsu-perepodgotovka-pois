#include "Chat.h"

#include <string>
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Chats
{
    Chat::Chat(const long id, std::string name) : Entity(id), _name{std::move(name)}
    {
    }

    std::string_view Chat::GetName() const
    {
        return _name;
    }
}
