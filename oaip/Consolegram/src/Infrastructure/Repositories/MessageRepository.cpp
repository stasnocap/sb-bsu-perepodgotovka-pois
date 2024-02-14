#include "../../SharedKernel/Repository.h"
#include "../../SharedKernel/Config.h"
#include "../../Domain/Messages/MessageRepository.h"

namespace Consolegram::Domain::Messages
{
    constexpr int MaxMessageTextLength{100};

    MessageRepository::MessageRepository(const SharedKernel::Config& config) : Repository{
        config["MessagesFileRelativePath"],
        [](std::ifstream& fileStream)
        {
            std::vector<Message> messages{};

            long id{};
            long userId{};
            long chatId{};
            char text[MaxMessageTextLength]{};

            while (!fileStream.eof())
            {
                fileStream >> id;
                fileStream >> userId;
                fileStream >> chatId;

                fileStream.get();
                fileStream.getline(text, MaxMessageTextLength,
                                   '\n');

                messages.emplace_back(id, userId, chatId, text);
            }

            return messages;
        }
    }
    {
    }

    std::vector<Message> MessageRepository::GetLastMessages(std::vector<long>& chatIds)
    {
        const std::vector<Message>& messages{GetAll()};

        const std::vector filteredByChatIds{
            SharedKernel::Where<Message>(messages, [&chatIds](const Message& message)
            {
                return std::ranges::any_of(chatIds, [&message](const long chatId)
                {
                    return message.GetChatId() == chatId;
                });
            })
        };

        std::vector<Message> lastMessages{};
        for (const Message& msg : filteredByChatIds)
        {
            const std::vector filteredByChatId{
                SharedKernel::Where<Message>(filteredByChatIds, [&msg](const Message& item)
                {
                    return msg.GetChatId() == item.GetChatId();
                })
            };

            if (const Message& maxIdMessage{
                *std::ranges::max_element(filteredByChatId,
                                          [](const Message& first, const Message& second)
                                          {
                                              return first.GetId() < second.GetId();
                                          })
            }; maxIdMessage.GetId() > msg.GetId())
            {
                lastMessages.push_back(maxIdMessage);
            }
        }

        return lastMessages;
    }
}