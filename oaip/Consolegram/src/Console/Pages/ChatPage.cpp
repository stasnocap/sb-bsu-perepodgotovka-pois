#include "ChatPage.h"

#include <iostream>

#include "../View/Colorizer.h"
#include "../View/Formatter.h"
#include "Messages/MessageRepository.h"
#include "Messages/GetChatMessages/GetChatMessagesHandler.h"
#include "Users/UserRepository.h"

namespace Consolegram::Console::Pages::Chat
{
    using namespace Domain;

    bool Show(const Chats::Chat* chat, Messages::MessageRepository& messageRepository,
              Users::UserRepository& userRepository)
    {
        const SharedKernel::ResultT getChatMessagesResult{
            Application::Messages::GetChatMessages::Handle(chat->GetId(), messageRepository, userRepository)
        };

        if (getChatMessagesResult.IsFailure())
        {
            std::cout << getChatMessagesResult.GetError() << '\n';
            return false;    
        }

        std::cout
            << View::Colorizer::SetGrayColor() << View::Colorizer::ChatSeparator;

        const std::vector users{getChatMessagesResult.GetValue().GetUsers()};
        for (const Messages::Message& message : getChatMessagesResult.GetValue().GetMessages())
        {
            auto user{
                std::ranges::find_if(users, [&message](const Users::User& item)
                {
                    return item.GetId() == message.GetUserId();
                })
            };

            if (user == users.end())
            {
                throw std::invalid_argument("User was not found");
            }

            std::cout
                << View::Colorizer::SetGrayColor()
                << View::Colorizer::SetPurpleColor() << user->GetName() << '\n'
                << View::Colorizer::SetGrayColor()
                << View::Colorizer::SetDarkYellowColor() << View::Formatter::FormatMessageText(message.GetText()) <<
                '\n'
                << View::Colorizer::SetGrayColor() << View::Colorizer::ChatSeparator;
        }

        std::cout << View::Colorizer::SetBlackColor();

        return true;
    }
}
