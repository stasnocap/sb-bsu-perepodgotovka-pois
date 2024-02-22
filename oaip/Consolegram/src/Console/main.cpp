#include "AuthenticationService.h"

#include "Pages/HomePage.h"
#include "Controls/HomeControls.h"
#include "Pages/ChatPage.h"

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

    const Users::User* currentUser{AuthenticationService::Authenticate(userRepository)};
    
    Pages::Home::Show(currentUser, participantRepository, chatRepository, messageRepository);
    const Chats::Chat* chat{Controls::Home::SelectChat(chatRepository)};
    Pages::Chat::Show(chat, messageRepository, userRepository);

    return EXIT_SUCCESS;
}
