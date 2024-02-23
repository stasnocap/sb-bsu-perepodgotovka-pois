#include "GetChatsWithLastMessagesHandler.h"

namespace Consolegram::Application::Chats::GetChatsWithLastMessages
{
    SharedKernel::ResultT<GetChatsWithLastMessagesResponse> Handle(
        const long userId,
        Domain::Participants::ParticipantRepository& participantRepository,
        Domain::Chats::ChatRepository& chatRepository,
        Domain::Messages::MessageRepository& messageRepository
    )
    {
        std::vector chatIds{participantRepository.GetChatsIds(userId)};

        if (chatIds.empty())
        {
            return SharedKernel::ResultT{false, GetChatsWithLastMessagesResponse{{}, {}}, "You have no chats"};
        }

        const std::vector chats{chatRepository.Get(chatIds)};

        const std::vector messages{messageRepository.GetLastMessages(chatIds)};

        return SharedKernel::ResultT<GetChatsWithLastMessagesResponse>::Success(GetChatsWithLastMessagesResponse{chats, messages});
    }
}