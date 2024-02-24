#include "CreateMessageHandler.h"

namespace Consolegram::Application::Messages::CreateMessage
{
    SharedKernel::Result Handle(const long userId, const long chatId, const std::string_view messageText,
                                Domain::Messages::MessageRepository& messageRepository)
    {
        if (messageText.size() >= Domain::Messages::MaxMessageTextLength)
        {
            return SharedKernel::Result::Failure(std::format("Message length can't be more than {}",
                                                             Domain::Messages::MaxMessageTextLength));
        }

        try
        {
            const Domain::Messages::Message message{
                messageRepository.GetNewId(), userId, chatId, messageText.data()
            };

            messageRepository.Add(message);

            messageRepository.SaveChanges();
        }
        catch ([[maybe_unused]] const std::exception& exception)
        {
            return SharedKernel::Result::Failure("Something went wrong");
        }

        return SharedKernel::Result::Success();
    }
}