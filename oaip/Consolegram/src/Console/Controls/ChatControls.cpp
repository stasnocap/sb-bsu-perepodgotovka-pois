﻿#include "ChatControls.h"

#include <iostream>

#include "Chats/Chat.h"
#include "Messages/MessageRepository.h"
#include "Messages/CreateMessage/CreateMessageHandler.h"
#include "Participants/ParticipantRepository.h"
#include "Users/User.h"

namespace Consolegram::Console::Controls::Chat
{
    void WriteMessage(const Domain::Users::User* user,
                      const Domain::Chats::Chat* chat,
                      Domain::Messages::MessageRepository& messageRepository,
                      Domain::Participants::ParticipantRepository& participantRepository)
    {
        if (participantRepository.CanWrite(user->GetId(), chat->GetId()))
        {
            while (true)
            {
                const std::string messageText{SharedKernel::Common::GetString("Please, write a message:")};

                if (messageText[0] == SharedKernel::Common::ExitKey)
                {
                    break;
                }

                if (const SharedKernel::Result createMessageResult{
                    Application::Messages::CreateMessage::Handle(user->GetId(), chat->GetId(), messageText,
                                                                 messageRepository)
                }; createMessageResult.IsFailure())
                {
                    std::cout << createMessageResult.GetError() << '\n';
                }
            }
        }
        else
        {
            SharedKernel::Common::GetString("Hit enter to exit.", [](const std::string_view input)
            {
                if (input[0] == SharedKernel::Common::ExitKey)
                {
                    return true;
                }

                return false;
            });
        }
    }
}