#include "ChatPage.h"

#include <iostream>

#include "../View/Colorizer.h"
#include "../View/Formatter.h"
#include "Messages/MessageRepository.h"
#include "Users/UserRepository.h"

namespace Consolegram::Console::Pages::Chat
{
    using namespace Domain;

    void Show(const Chats::Chat* chat, Messages::MessageRepository& messageRepository,
              Users::UserRepository& userRepository)
    {
        const std::vector messages{messageRepository.GetLastChatMessages(chat->GetId())};
        const std::vector users{userRepository.GetUsersByMessages(messages)};

        std::cout
            << View::Colorizer::SetGrayColor() << View::Colorizer::ChatSeparator;
        
        for (const Messages::Message& message : messages)
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
                    << View::Colorizer::SetDarkYellowColor() << View::Formatter::FormatMessageText(message.GetText()) << '\n'
                << View::Colorizer::SetGrayColor() << View::Colorizer::ChatSeparator;
        }

        std::cout << View::Colorizer::SetBlackColor();
    }
}
