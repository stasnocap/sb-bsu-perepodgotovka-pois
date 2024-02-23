#include "ChatControls.h"

#include <iostream>

#include "Chats/Chat.h"
#include "Messages/MessageRepository.h"
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
                const std::string messageText{
                    SharedKernel::Common::GetString("Please, write a message:", [](const std::string_view input)
                    {
                        if (input.size() >= Domain::Messages::MaxMessageTextLength)
                        {
                            std::cout
                                << "Message length can't be more than " << Domain::Messages::MaxMessageTextLength
                                << '\n';
                            return false;
                        }

                        return true;
                    })
                };

                if (messageText[0] == SharedKernel::Common::ExitKey)
                {
                    break;
                }

                const Domain::Messages::Message message{
                    messageRepository.GetNewId(), user->GetId(), chat->GetId(), messageText
                };

                messageRepository.Add(message);

                messageRepository.SaveChanges();
            }
        } else
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

        // remove remained \n
        std::cin.get();
    }
}
