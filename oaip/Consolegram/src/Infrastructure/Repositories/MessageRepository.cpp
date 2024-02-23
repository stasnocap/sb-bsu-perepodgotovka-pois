#include "../../SharedKernel/Repository.h"
#include "../../SharedKernel/Config.h"
#include "../../Domain/Messages/MessageRepository.h"

#include <sstream>

namespace Consolegram::Domain::Messages
{
    constexpr int ChatPageMessagesCount{10};

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
        },
        [](const Message& chat)
        {
            std::ostringstream oStringStream{};

            oStringStream
                << chat.GetId() << '\t'
                << chat.GetUserId() << '\t'
                << chat.GetChatId() << '\t'
                << chat.GetText();

            return oStringStream.str();
        }
    }
    {
    }

    std::vector<Message> MessageRepository::GetLastMessages(std::vector<long>& chatIds)
    {
        const std::vector<Message>& messages{GetAll()};

        const std::vector filteredByChatIds{
            SharedKernel::Common::Where<Message>(messages, [&chatIds](const Message& message)
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
                SharedKernel::Common::Where<Message>(filteredByChatIds, [&msg](const Message& item)
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

    std::vector<Message> MessageRepository::GetLastChatMessages(const long chatId)
    {
        const std::vector<Message>& messages{GetAll()};

        std::vector filteredByChatId{
            SharedKernel::Common::Where<Message>(messages, [chatId](const Message& message)
            {
                return chatId == message.GetChatId();
            })
        };

        if (filteredByChatId.size() <= ChatPageMessagesCount)
        {
            return filteredByChatId;           
        }

        std::vector lastMessages(filteredByChatId.end() - ChatPageMessagesCount, filteredByChatId.end());

        return lastMessages;
    }
}
