#include <iostream>

#include "Controls/ChatControls.h"
#include "Pages/HomePage.h"
#include "Controls/HomeControls.h"
#include "Pages/AuthenticatePage.h"
#include "Pages/ChatPage.h"
#include "Pages/GoodbyePage.h"
#include "Pages/HelpPage.h"

int main(int argc, char* argv[])
{
    using namespace Consolegram;
    using namespace Consolegram::Domain;
    using namespace Consolegram::Console;

    SharedKernel::Config config{};
    config.Init(argc, argv);

    Users::UserRepository userRepository{config};
    Participants::ParticipantRepository participantRepository{config};
    Messages::MessageRepository messageRepository{config};
    Chats::ChatRepository chatRepository{config};

    Pages::Help::Show();

    while (true)
    {
        const Users::User* currentUser{Pages::Authenticate::Show(userRepository)};
        if (!currentUser)
        {
            break;
        }

        while (true)
        {
            if (!Pages::Home::Show(currentUser, participantRepository, chatRepository, messageRepository))
            {
                break;
            }

            const Chats::Chat* selectedChat{Controls::Home::SelectChat(chatRepository)};
            if (!selectedChat)
            {
                break;
            }

            if (!Pages::Chat::Show(selectedChat, messageRepository, userRepository))
            {
                break;
            }

            Controls::Chat::WriteMessage(currentUser, selectedChat, messageRepository, participantRepository);
        }
    }

    Pages::Goodbye::Show();

    return EXIT_SUCCESS;
}