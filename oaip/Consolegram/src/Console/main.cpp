#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <format>
#include <functional>
#include <windows.h>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

namespace Cgram
{
    constexpr std::string_view EnvironmentKey{"--environment"};
    constexpr std::string_view DevelopmentEnvironment{"development"};
    constexpr std::string_view ProductionEnvironment{"production"};
    constexpr std::string_view AppsettingsFileNameWithoutExtension{"appsettings"};
    constexpr std::string_view ChatSeparator{"------------------------------------\n"};

    constexpr int MaxChatNameLength{30};
    constexpr int MaxMessageTextLength{100};

    enum ChangeType
    {
        None,
        Add,
        Remove,
        Update,
    };

    template <typename T>
    struct Change
    {
        ChangeType Type{};
        T Value{};
    };
    
    template <typename TEntity, typename TResult>
    std::vector<TResult> Select(const std::vector<TEntity>& entities,
                                const std::function<TResult(TEntity)>& selector)
    {
        std::vector<TResult> selects{};
        selects.reserve(entities.size());
        for (const TEntity& entity : entities)
        {
            selects.push_back(selector(entity));
        }
        return selects;
    }

    template <typename TEntity>
    std::vector<TEntity> Where(const std::vector<TEntity>& entities,
                               const std::function<bool(TEntity)>& predicate)
    {
        std::vector<TEntity> filtered{};
        std::copy_if(entities.begin(), entities.end(), std::back_inserter(filtered),
                     [&predicate](const TEntity& entity)
                     {
                         return predicate(entity);
                     });
        return filtered;
    }

    class Entity
    {
        long _id{};

    public:
        explicit Entity(const long id) : _id{id}
        {
        }

        [[nodiscard]] long GetId() const
        {
            return _id;
        }
    };

    class User : public Entity
    {
        std::string _name{};
        std::string _password{};

    public:
        explicit User(const long id, std::string userName, std::string password)
            : Entity(id), _name{std::move(userName)}, _password{std::move(password)}
        {
        }

        [[nodiscard]] std::string_view GetUserName() const
        {
            return _name;
        }

        [[nodiscard]] std::string_view GetPassword() const
        {
            return _password;
        }
    };

    class Participant : public Entity
    {
        long _userId{};
        long _chatId{};
        bool _canWrite{};

    public:
        explicit Participant(const long id, const long userId, const long chatId, const bool canWrite)
            : Entity(id), _userId{userId}, _chatId{chatId}, _canWrite{canWrite}
        {
        }

        [[nodiscard]] long GetUserId() const
        {
            return _userId;
        }

        [[nodiscard]] long GetChatId() const
        {
            return _chatId;
        }

        [[nodiscard]] long CanWrite() const
        {
            return _canWrite;
        }
    };

    class Message : public Entity
    {
        long _userId{};
        long _chatId{};
        std::string _text{};

    public:
        explicit Message(const long id, const long userId, const long chatId, std::string text)
            : Entity(id), _userId{userId}, _chatId{chatId}, _text{std::move(text)}
        {
        }

        [[nodiscard]] long GetUserId() const
        {
            return _userId;
        }

        [[nodiscard]] long GetChatId() const
        {
            return _chatId;
        }

        [[nodiscard]] std::string_view GetText() const
        {
            return _text;
        }
    };

    class Chat : public Entity
    {
        std::string _name{};

    public:
        explicit Chat(const long id, std::string name) : Entity(id), _name{std::move(name)}
        {
        }

        [[nodiscard]] std::string_view GetName() const
        {
            return _name;
        }
    };

    template <typename T>
    class Repository
    {
        std::vector<T> _cachedEntities{};
        std::vector<Change<T>> _changeTracker{};
        typename std::vector<T>::iterator _end{};
        std::string _fileName{};
        std::function<std::vector<T>(std::ifstream&)> _fileReader{};

    public:
        explicit Repository(std::string fileName,
                            std::function<std::vector<T>(std::ifstream&)> fileReader)
            : _fileName{std::move(fileName)}, _fileReader{std::move(fileReader)}
        {
        }

        typename std::vector<T>::iterator End()
        {
            return _end;
        }

        void Add(const T& entity)
        {
            _changeTracker.push_back({Cgram::Add, entity});
        }

        void Remove(const T& entity)
        {
            _changeTracker.push_back({Cgram::Remove, entity});
        }

        void Update(const T& entity)
        {
            _changeTracker.push_back({Cgram::Update, entity});
        }

        auto Get(long id) const
        {
            const std::vector<T>& entities{GetAll()};
            return std::find_if(entities.begin(), entities.End(), [&id](const T& item)
            {
                return item.getId() == id;
            });
        }

        std::vector<T> Get(std::vector<long>& ids)
        {
            const std::vector<T>& entities{GetAll()};
            return Where<T>(entities, [&ids](const T& entity)
            {
                return std::any_of(ids.begin(), ids.end(), [&entity](long id)
                {
                    return entity.GetId() == id;
                });
            });
        }

        std::vector<T>& GetAll()
        {
            if (!_cachedEntities.empty())
            {
                return _cachedEntities;
            }

            std::ifstream fileStream{_fileName.data()};

            if (!fileStream.is_open())
            {
                throw std::invalid_argument(std::format("The {} cannot be opened!", _fileName));
            }

            std::vector<T> entities{_fileReader(fileStream)};

            fileStream.close();

            _cachedEntities = entities;
            _end = _cachedEntities.end();

            return _cachedEntities;
        }

        void SaveChanges()
        {
            std::vector<T>& entities{GetAll()};

            for (Change<T>& change : _changeTracker)
            {
                if (change.value.get_id() < 1)
                {
                    throw std::invalid_argument("Id can't be zero or below");
                }

                switch (change.type)
                {
                case Cgram::Add:
                    if (std::any_of(entities.begin(), entities.End(), [&change](const T& item)
                    {
                        return change.value.getId() == item.getId();
                    }))
                    {
                        throw std::invalid_argument(std::format("{} with id({}) already exists",
                                                                typeid(T).name(),
                                                                change.value.getId()));
                    }

                    entities.push_back(change.value);
                    break;
                case Cgram::Remove:
                    {
                        const auto entity{get(change.value.getId())};
                        if (entity == entities.End())
                        {
                            throw std::invalid_argument(std::format("{} with id({}) was not found",
                                                                    typeid(T).name(),
                                                                    change.value.getId()));
                        }

                        entities.erase(entity);
                    }
                    break;
                case Cgram::Update:
                    {
                        const auto entity{get(change.value.getId())};
                        if (entity == entities.End())
                        {
                            throw std::invalid_argument(std::format("{} with id({}) was not found",
                                                                    typeid(T).name(),
                                                                    change.value.getId()));
                        }

                        entities.erase(entity);
                        entities.push_back(change.value);
                    }
                    break;
                case None:
                default:
                    throw std::invalid_argument("Change was not implemented");
                }
            }

            _changeTracker.clear();
        }
    };

    namespace Common
    {
        std::string GetString(const std::string_view ask)
        {
            std::cout << ask;
            std::string input{};
            std::getline(std::cin >> std::ws, input);
            return input;
        }

        template <typename T>
        std::string ToLower(T& data)
        {
            std::string lower{data};
            std::transform(lower.begin(), lower.end(), lower.begin(),
                           [](const unsigned char c) { return std::tolower(c); });
            return lower;
        }
    }

    class Config
    {
        std::map<std::string, std::string> _settings{};
        bool _isDevelopment{};
        bool _isProduction{};

        void ReadSettings(std::string_view appsettingsFileName, bool isRequired)
        {
            std::ifstream iFileStream(appsettingsFileName.data());

            if (!iFileStream.is_open())
            {
                if (isRequired)
                {
                    throw std::invalid_argument(std::format("The {} cannot be opened!", appsettingsFileName));
                }

                return;
            }

            iFileStream.get();
            iFileStream.get();
            iFileStream.get();

            std::string line{};
            while (std::getline(iFileStream, line))
            {
                std::istringstream iStringStream(line);

                std::string key{};
                if (!std::getline(iStringStream, key, '='))
                {
                    break;
                }

                std::string value{};
                if (!std::getline(iStringStream, value))
                {
                    break;
                }

                _settings[key] = value;
            }
        }

        std::string GetEnvironment(const int argc, char* argv[])
        {
            std::string environment{};
            for (int i = 1; i < argc; ++i)
            {
                const std::string lowerArg{Common::ToLower(argv[i])};
                if (lowerArg == EnvironmentKey && i + 1 < argc)
                {
                    const std::string nextLowerArg{Common::ToLower(argv[i + 1])};
                    if (nextLowerArg == ProductionEnvironment)
                    {
                        environment = ProductionEnvironment;
                        _isDevelopment = false;
                        _isProduction = true;
                        break;
                    }
                }
            }

            if (environment.empty())
            {
                environment = DevelopmentEnvironment;
                _isDevelopment = true;
                _isProduction = false;
            }

            return environment;
        }

    public:
        std::string operator[](const std::string& key) const
        {
            return _settings.at(key);
        }

        [[nodiscard]] bool IsDevelopment() const
        {
            return _isDevelopment;
        }

        [[nodiscard]] bool IsProduction() const
        {
            return _isProduction;
        }

        void Init(const int argc, char* argv[])
        {
            std::string environment(GetEnvironment(argc, argv));
            environment[0] = static_cast<char>(std::toupper(environment[0]));
            ReadSettings(std::format("{}.txt", AppsettingsFileNameWithoutExtension), true);
            ReadSettings(std::format("{}.{}.txt", AppsettingsFileNameWithoutExtension, environment), false);
        }
    };

    class UserRepository : public Repository<User>
    {
    public:
        explicit UserRepository(const Config& config) : Repository{
            config["UsersFileRelativePath"],
            [](std::ifstream& fileStream)
            {
                std::vector<User> users{};

                long id{};
                std::string userName{};
                std::string password{};

                while (!fileStream.eof())
                {
                    fileStream >> id;
                    fileStream >> userName;
                    fileStream >> password;

                    users.emplace_back(id, userName,
                                       password);
                }

                return users;
            }
        }
        {
            auto m{config["UsersFileRelativePath"]};
        }

        std::vector<User>::iterator GetByUserName(std::string_view userName)
        {
            std::vector<User>& entities{GetAll()};
            return std::ranges::find_if(entities, [userName](const User& item)
            {
                return item.GetUserName() == userName;
            });
        }
    };

    class ParticipantRepository : public Repository<Participant>
    {
    public:
        explicit ParticipantRepository(const Config& config) : Repository{
            config["ParticipantsFileRelativePath"], [](std::ifstream& fileStream)
            {
                std::vector<Participant> participants{};

                long id{};
                long userId{};
                long chatId{};
                std::string canWrite{};

                while (!fileStream.eof())
                {
                    fileStream >> id;
                    fileStream >> userId;
                    fileStream >> chatId;
                    fileStream >> canWrite;

                    participants.emplace_back(id, userId, chatId, canWrite == "true");
                }

                return participants;
            }
        }
        {
        }

        std::vector<long> GetChatsIds(long userId)
        {
            const std::vector<Participant>& participants{GetAll()};

            const std::vector filteredByUserId{
                Where<Participant>(participants, [userId](const Participant& participant)
                {
                    return participant.GetUserId() == userId;
                })
            };

            return Select<Participant, long>(filteredByUserId, [](const Participant& participant)
            {
                return participant.GetChatId();
            });
        }
    };

    class ChatRepository : public Repository<Chat>
    {
    public:
        explicit ChatRepository(const Config& config) : Repository{
            config["ChatsFileRelativePath"], [](std::ifstream& fileStream)
            {
                std::vector<Chat> chats{};

                long id{};
                char name[MaxChatNameLength]{};

                while (!fileStream.eof())
                {
                    fileStream >> id;

                    fileStream.get();
                    fileStream.getline(name, MaxChatNameLength, '\n');

                    chats.emplace_back(id, name);
                }

                return chats;
            }
        }
        {
        }
    };

    class MessageRepository : public Repository<Message>
    {
    public:
        explicit MessageRepository(const Config& config) : Repository{
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

        std::vector<Message> GetLastMessages(std::vector<long>& chatIds)
        {
            const std::vector<Message>& messages{GetAll()};

            const std::vector filteredByChatIds{
                Where<Message>(messages, [&chatIds](const Message& message)
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
                    Where<Message>(filteredByChatIds, [&msg](const Message& item)
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
    };

    User* Authenticate(UserRepository& usersRepository)
    {
        while (true)
        {
            const std::string userName{Common::GetString("Please, login.\nEnter username:")};

            const auto user{usersRepository.GetByUserName(userName)};

            if (user == usersRepository.End())
            {
                std::cout << "User with such username was not found\n";
                continue;
            }

            const std::string password{Common::GetString("Enter password:")};

            if (user->GetPassword() != password)
            {
                std::cout << "Password is incorrect\n";
                continue;
            }

            return user._Ptr;
        }
    }

    namespace Cview
    {
        std::string_view SetColor(const HANDLE hConsole, const WORD wAttributes)
        {
            SetConsoleTextAttribute(hConsole, wAttributes);
            return "";
        }

        std::string_view SetBlueColor(const HANDLE hConsole)
        {
            return SetColor(hConsole, 1);
        }

        std::string_view SetBlackColor(const HANDLE hConsole)
        {
            return SetColor(hConsole, 0);
        }

        std::string_view SetDarkYellowColor(const HANDLE hConsole)
        {
            return SetColor(hConsole, 6);
        }

        std::string_view SetGrayColor(const HANDLE hConsole)
        {
            return SetColor(hConsole, 8);
        }

        std::string_view SetPurpleColor(const HANDLE hConsole)
        {
            return SetColor(hConsole, 5);
        }
    }

    void ShowHomePage(
        const User* user,
        ParticipantRepository& participantRepository,
        ChatRepository& chatRepository,
        MessageRepository& messageRepository
    )
    {
        std::vector chatIds{participantRepository.GetChatsIds(user->GetId())};
        const std::vector chats{chatRepository.Get(chatIds)};
        std::vector messages{messageRepository.GetLastMessages(chatIds)};

        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        for (const Chat& chat : chats)
        {
            auto msg{
                std::ranges::find_if(messages, [&chat](const Message& item)
                {
                    return chat.GetId() == item.GetChatId();
                })
            };

            std::cout
                << Cview::SetGrayColor(hConsole) << ChatSeparator << "--- "
                << Cview::SetBlueColor(hConsole) << chat.GetName() << '\n';

            if (msg != messages.end())
            {
                std::cout
                    << Cview::SetGrayColor(hConsole) << '-'
                    << Cview::SetPurpleColor(hConsole) << chat.GetId()
                    << Cview::SetGrayColor(hConsole) << "- "
                    << Cview::SetDarkYellowColor(hConsole)
                    << msg->GetText().substr(0, ChatSeparator.size() - 5) << '\n';
            }
        }

        std::cout << Cview::SetGrayColor(hConsole) << ChatSeparator;
    }
}

int main(int argc, char* argv[])
{
    Cgram::Config config{};
    config.Init(argc, argv);

    Cgram::UserRepository userRepository{config};
    Cgram::ParticipantRepository participantRepository{config};
    Cgram::MessageRepository messageRepository{config};
    Cgram::ChatRepository chatRepository{config};

    const Cgram::User* currentUser{Authenticate(userRepository)};
    ShowHomePage(currentUser, participantRepository, chatRepository, messageRepository);
    return EXIT_SUCCESS;
}