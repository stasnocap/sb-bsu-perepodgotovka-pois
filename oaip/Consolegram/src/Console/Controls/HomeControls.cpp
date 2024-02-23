#include "HomeControls.h"

#include <iostream>

#include "Common.h"
#include "Chats/ChatRepository.h"

namespace Consolegram::Console::Controls::Home
{
    using namespace Domain;
    
    Chats::Chat* SelectChat(Chats::ChatRepository& chatRepository)
    {
        std::vector<Chats::Chat>::const_iterator chatIterator;
        SharedKernel::Common::GetInt("Select a chat number:", [&chatRepository, &chatIterator](const int chatId)
        {
            if (chatId == SharedKernel::Common::ExitCode)
            {
                chatIterator._Ptr = nullptr;
                return true;
            }
            
            chatIterator = chatRepository.Get(chatId);

            if (chatIterator == chatRepository.End())
            {
                std::cout << "Selected chat was not found!\n";
                return false;
            }
            
            return true;
        });

        if (!chatIterator._Ptr)
        {
            return nullptr;
        }

        return chatIterator._Ptr;
    }
}
