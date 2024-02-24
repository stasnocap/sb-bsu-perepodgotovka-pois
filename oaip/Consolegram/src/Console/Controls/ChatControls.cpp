#include "ChatControls.h"

#include <iostream>

#include "Chats/Chat.h"
#include "Messages/MessageRepository.h"
#include "Messages/CreateMessage/CreateMessageHandler.h"
#include "Participants/ParticipantRepository.h"
#include "Users/User.h"
#include "../Input.h"

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
                const std::string messageText{GetString("Please, write a message:")};

                if (messageText[0] == ExitKey)
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
            GetString("Hit enter to exit.", [](const std::string_view input)
            {
                if (input[0] == ExitKey)
                {
                    return true;
                }

                return false;
            });
        }
    }
}