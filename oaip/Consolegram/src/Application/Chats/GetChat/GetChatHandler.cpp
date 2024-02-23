#include "GetChatHandler.h"

namespace Consolegram::Application::Chats::GetChat
{
    SharedKernel::ResultT<Domain::Chats::Chat*> Handle(const long id, Domain::Chats::ChatRepository& chatRepository)
    {
        const auto chat{chatRepository.Get(id)};

        if (chat == chatRepository.End())
        {
            return SharedKernel::ResultT<Domain::Chats::Chat*>::Failure("Chat was not found");
        }

        return SharedKernel::ResultT<Domain::Chats::Chat*>::Success(chat._Ptr);
    }
}
