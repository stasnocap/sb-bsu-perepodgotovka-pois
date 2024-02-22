#include "HomeControls.h"

#include "Common.h"
#include "Chats/ChatRepository.h"

namespace Consolegram::Console::Controls::Home
{
    using namespace Domain;

    Chats::Chat* SelectChat(Chats::ChatRepository& chatRepository)
    {
        std::vector<Chats::Chat>::const_iterator chatIterator;
        SharedKernel::GetInt("Select a chat number:", [&chatRepository, &chatIterator](const int chatId)
        {
            chatIterator = chatRepository.Get(chatId);
            return chatIterator != chatRepository.End();
        });

        return chatIterator._Ptr;
    }
}
