#include <iostream>

#include "AuthenticationService.h"
#include "Controls/ChatControls.h"
#include "Pages/HomePage.h"
#include "Controls/HomeControls.h"
#include "Pages/AuthenticatePage.h"
#include "Pages/ChatPage.h"

int SuccessExit()
{
    std::cout << "Goodbye!";
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    using namespace Consolegram::SharedKernel;
    using namespace Consolegram::Domain;
    using namespace Consolegram::Application;
    using namespace Consolegram::Console;

    Config config{};
    config.Init(argc, argv);

    Users::UserRepository userRepository{config};
    Participants::ParticipantRepository participantRepository{config};
    Messages::MessageRepository messageRepository{config};
    Chats::ChatRepository chatRepository{config};

    std::cout << "Tip: hit enter to exit or go back.\n";

    const Users::User* currentUser{Pages::Authenticate::Show(userRepository)};
    if (!currentUser)
    {
        return SuccessExit();
    }

    while (true)
    {
        if (!Pages::Home::Show(currentUser, participantRepository, chatRepository, messageRepository))
        {
            return SuccessExit();
        }

        const Chats::Chat* selectedChat{Controls::Home::SelectChat(chatRepository)};
        if (!selectedChat)
        {
            return SuccessExit();
        }

        Pages::Chat::Show(selectedChat, messageRepository, userRepository);

        Controls::Chat::WriteMessage(currentUser, selectedChat, messageRepository, participantRepository);
    }
}