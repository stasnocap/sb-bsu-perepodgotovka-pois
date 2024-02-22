#include "HomePage.h"

#include <iostream>
#include "../View/Colorizer.h"

namespace Consolegram::Console::Pages::Home
{
    using namespace Domain;

    void Show(
        const Users::User* user,
        Participants::ParticipantRepository& participantRepository,
        Chats::ChatRepository& chatRepository,
        Messages::MessageRepository& messageRepository
    )
    {
        std::vector chatIds{participantRepository.GetChatsIds(user->GetId())};
        const std::vector chats{chatRepository.Get(chatIds)};
        std::vector messages{messageRepository.GetLastMessages(chatIds)};

        for (const Chats::Chat& chat : chats)
        {
            auto msg{
                std::ranges::find_if(messages, [&chat](const Messages::Message& item)
                {
                    return chat.GetId() == item.GetChatId();
                })
            };

            std::cout
                << View::Colorizer::SetGrayColor() << View::Colorizer::ChatSeparator << "--- "
                << View::Colorizer::SetBlueColor() << chat.GetName() << '\n';

            if (msg != messages.end())
            {
                std::cout
                    << View::Colorizer::SetGrayColor() << '-'
                    << View::Colorizer::SetPurpleColor() << chat.GetId()
                    << View::Colorizer::SetGrayColor() << "- "
                    << View::Colorizer::SetDarkYellowColor()
                    << msg->GetText().substr(0, View::Colorizer::ChatSeparator.size() - 5) << '\n';
            }
        }

        std::cout
                << View::Colorizer::SetGrayColor() << View::Colorizer::ChatSeparator
                << View::Colorizer::SetBlackColor();
    }
}
