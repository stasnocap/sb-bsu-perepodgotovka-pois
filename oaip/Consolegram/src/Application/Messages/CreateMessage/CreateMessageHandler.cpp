#include "CreateMessageHandler.h"

namespace Consolegram::Application::Messages::CreateMessage
{
    SharedKernel::Result Handle(const long userId, const long chatId, std::string_view messageText,
                                Domain::Messages::MessageRepository& messageRepository)
    {
        try
        {
            const Domain::Messages::Message message{
                messageRepository.GetNewId(), userId, chatId, messageText.data()
            };

            messageRepository.Add(message);

            messageRepository.SaveChanges();
        } catch ([[maybe_unused]] const std::exception& exception)
        {
            return SharedKernel::Result::Failure("Something went wrong");
        }
        
        return SharedKernel::Result::Success();
    }
}
