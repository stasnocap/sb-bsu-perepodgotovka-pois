#include "../../Domain/Chats/ChatRepository.h"

#include <sstream>

namespace Consolegram::Domain::Chats
{
    constexpr int MaxChatNameLength{30};
    
    ChatRepository::ChatRepository(const SharedKernel::Config& config) : Repository{
        config["ChatsFileRelativePath"], [](std::ifstream& fileStream)
        {
            std::vector<Chat> chats{};

            long id{};
            char name[MaxChatNameLength]{};

            while (!fileStream.eof())
            {
                fileStream >> id;

                fileStream.get();
                fileStream.getline(name, MaxChatNameLength, '\n');

                chats.emplace_back(id, name);
            }

            return chats;
        },
        [](const Chat& chat)
        {
            std::ostringstream oStringStream{};
        
            oStringStream
                << chat.GetId() << '\t'
                << chat.GetName();
        
            return oStringStream.str();
        }
    }
    {
    }
};