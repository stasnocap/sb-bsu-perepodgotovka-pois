#include "HomePage.h"

#include <iostream>
#include "../View/Colorizer.h"
#include "Chats/GetChatsWithLastMessages/GetChatsWithLastMessagesHandler.h"

namespace Consolegram::Console::Pages::Home
{
    using namespace Domain;

    bool Show(
        const Users::User* user,
        Participants::ParticipantRepository& participantRepository,
        Chats::ChatRepository& chatRepository,
        Messages::MessageRepository& messageRepository
    )
    {
        const SharedKernel::ResultT getChatsWithLastMessagesResult{
            Application::Chats::GetChatsWithLastMessages::Handle(
                user->GetId(),
                participantRepository,
                chatRepository,
                messageRepository
            )
        };

        if (getChatsWithLastMessagesResult.IsFailure())
        {
            std::cout << getChatsWithLastMessagesResult.GetError() << '\n';
            return false;
        }

        std::vector messages{getChatsWithLastMessagesResult.GetValue().GetMessages()};
        for (const Chats::Chat& chat : getChatsWithLastMessagesResult.GetValue().GetChats())
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
            << View::Colorizer::SetWhiteColor();

        return true;
    }
}
