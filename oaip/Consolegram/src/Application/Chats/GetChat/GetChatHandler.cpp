#include "GetChatHandler.h"

namespace Consolegram::Application::Chats::GetChat
{
    Result<Domain::Chats::Chat*> Handle(const long id, Domain::Chats::ChatRepository& chatRepository)
    {
        const auto chat{chatRepository.Get(id)};

        if (chat == chatRepository.End())
        {
            return Result<Domain::Chats::Chat*>::Failure("Chat was not found");
        }

        return Result<Domain::Chats::Chat*>::Success(chat._Ptr);
    }
}
