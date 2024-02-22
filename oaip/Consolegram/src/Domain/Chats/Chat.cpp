#include "Chat.h"

#include <sstream>
#include <string>
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Chats
{
    Chat::Chat(const long id, std::string name) : SharedKernel::Entity(id), _name{std::move(name)}
    {
    }

    std::string_view Chat::GetName() const
    {
        return _name;
    }

    std::string Chat::ToFileString() const
    {
        std::ostringstream oStringStream{};
        
        oStringStream
            << GetId() << '\t'
            << GetName();
        
        return oStringStream.str();
    }
}
