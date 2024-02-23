#include "GetChatsWithLastMessagesHandler.h"

namespace Consolegram::Application::Chats::GetChatsWithLastMessages
{
    Result<GetChatsWithLastMessagesResponse> Handle(
        const long userId,
        Domain::Participants::ParticipantRepository& participantRepository,
        Domain::Chats::ChatRepository& chatRepository,
        Domain::Messages::MessageRepository& messageRepository
    )
    {
        std::vector chatIds{participantRepository.GetChatsIds(userId)};

        if (chatIds.empty())
        {
            return Result{false, GetChatsWithLastMessagesResponse{{}, {}}, "You have no chats"};
        }

        const std::vector chats{chatRepository.Get(chatIds)};

        const std::vector messages{messageRepository.GetLastMessages(chatIds)};

        return Result<GetChatsWithLastMessagesResponse>::Success(GetChatsWithLastMessagesResponse{chats, messages});
    }
}