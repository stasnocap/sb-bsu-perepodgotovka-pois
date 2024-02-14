#include "HomePage.h"

#include <iostream>
#include <windows.h>
#include "../View/Colorizer.h"

namespace Consolegram::Console::Pages::HomePage
{
    constexpr std::string_view ChatSeparator{"------------------------------------\n"};

    void ShowHomePage(
        const Domain::Users::User* user,
        Domain::Participants::ParticipantRepository& participantRepository,
        Domain::Chats::ChatRepository& chatRepository,
        Domain::Messages::MessageRepository& messageRepository
    )
    {
        std::vector chatIds{participantRepository.GetChatsIds(user->GetId())};
        const std::vector chats{chatRepository.Get(chatIds)};
        std::vector messages{messageRepository.GetLastMessages(chatIds)};

        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        for (const Domain::Chats::Chat& chat : chats)
        {
            auto msg{
                std::ranges::find_if(messages, [&chat](const Domain::Messages::Message& item)
                {
                    return chat.GetId() == item.GetChatId();
                })
            };

            std::cout
                << View::Colorizer::SetGrayColor(hConsole) << ChatSeparator << "--- "
                << View::Colorizer::SetBlueColor(hConsole) << chat.GetName() << '\n';

            if (msg != messages.end())
            {
                std::cout
                    << View::Colorizer::SetGrayColor(hConsole) << '-'
                    << View::Colorizer::SetPurpleColor(hConsole) << chat.GetId()
                    << View::Colorizer::SetGrayColor(hConsole) << "- "
                    << View::Colorizer::SetDarkYellowColor(hConsole)
                    << msg->GetText().substr(0, ChatSeparator.size() - 5) << '\n';
            }
        }

        std::cout << View::Colorizer::SetGrayColor(hConsole) << ChatSeparator;
    }
}
