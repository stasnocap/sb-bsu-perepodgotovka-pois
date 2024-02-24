#include "HomeControls.h"

#include <iostream>

#include "Common.h"
#include "../Input.h"
#include "Chats/ChatRepository.h"
#include "Chats/GetChat/GetChatHandler.h"

namespace Consolegram::Console::Controls::Home
{
    using namespace Domain;

    Chats::Chat* SelectChat(Chats::ChatRepository& chatRepository)
    {
        Chats::Chat* chat{nullptr};
        GetInt("Select a chat number:", [&chatRepository, &chat](const int chatId)
        {
            if (chatId == ExitCode)
            {
                return true;
            }

            const SharedKernel::ResultT getChatResult{Application::Chats::GetChat::Handle(chatId, chatRepository)};

            if (getChatResult.IsFailure())
            {
                std::cout << getChatResult.GetError() << '\n';
                return false;
            }

            chat = getChatResult.GetValue();
            return true;
        });

        return chat;
    }
}