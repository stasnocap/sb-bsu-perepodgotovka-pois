#include <format>
#include <functional>
#include <windows.h>

#include "AuthenticationService.h"
#include "Users/User.h"
#include "Config.h"
#include "Chats/ChatRepository.h"
#include "Messages/MessageRepository.h"
#include "Pages/HomePage.h"
#include "Participants/ParticipantRepository.h"
#include "Users/UserRepository.h"

int main(int argc, char* argv[])
{
    using namespace Consolegram::SharedKernel;
    using namespace Consolegram::Domain;
    using namespace Consolegram::Application;
    using namespace Consolegram::Console::Pages;

    Config config{};
    config.Init(argc, argv);

    Users::UserRepository userRepository{config};
    Participants::ParticipantRepository participantRepository{config};
    Messages::MessageRepository messageRepository{config};
    Chats::ChatRepository chatRepository{config};

    const Users::User* currentUser{AuthenticationService::Authenticate(userRepository)};
    HomePage::ShowHomePage(currentUser, participantRepository, chatRepository, messageRepository);
    return EXIT_SUCCESS;
}
