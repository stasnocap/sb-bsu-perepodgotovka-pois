#include "Chat.h"

#include <string>
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Chats
{
    Chat::Chat(const long id, std::string name) : SharedKernel::Entity(id), _name{std::move(name)}
    {
    }

    [[nodiscard]] std::string_view Chat::GetName() const
    {
        return _name;
    }
}