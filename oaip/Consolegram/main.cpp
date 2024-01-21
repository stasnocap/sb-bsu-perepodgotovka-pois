#include <iostream>
#include <vector>
#include <algorithm>
#include <format>
#include <functional>
#include <windows.h>

namespace cgram {
    enum ChangeType {
        none,
        add,
        remove,
        update,
    };

    template<typename T>
    struct Change {
        ChangeType type{};
        T value{};
    };


    template<typename TEntity, typename TResult>
    std::vector<TResult> select(const std::vector<TEntity> &entities,
                                const std::function<TResult(TEntity)> &selector) {
        std::vector<TResult> selects{};
        for (const TEntity &entity: entities) {
            selects.push_back(selector(entity));
        }
        return selects;
    }

    template<typename TEntity>
    std::vector<TEntity> where(const std::vector<TEntity> &entities,
                               const std::function<bool(TEntity)> &predicate) {
        std::vector<TEntity> filtered{};
        std::copy_if(entities.begin(), entities.end(), std::back_inserter(filtered),
                     [&predicate](const TEntity &entity) {
                         return predicate(entity);
                     });
        return filtered;
    }

    template<typename T>
    class Repository {
    private:
        std::vector<T> m_entities{};
        std::vector<Change<T>> m_changeTracker{};
        std::vector<T>::iterator m_end{};

    public:
        explicit Repository(const std::vector<T> &entities) : m_entities{entities} {
        }

        std::vector<T>::iterator &end() {
            return m_end;
        }

        void add(const T &entity) {
            m_changeTracker.push_back({cgram::add, entity});
        }

        void remove(const T &entity) {
            m_changeTracker.push_back({cgram::remove, entity});
        }

        void update(const T &entity) {
            m_changeTracker.push_back({cgram::update, entity});
        }

        std::vector<T>::iterator get(long id) {
            const std::vector<T> &entities{getAll()};
            return std::find_if(entities.begin(), entities.end(), [&id](const T &item) {
                return item.getId() == id;
            });
        }

        std::vector<T> get(std::vector<long> &ids) {
            const std::vector<T> &entities{getAll()};
            return where<T>(entities, [&ids](const T &entity) {
                return std::any_of(ids.begin(), ids.end(), [&entity](long id) {
                    return entity.getId() == id;
                });
            });
        }

        std::vector<T> &getAll() {
            m_end = m_entities.end();
            return m_entities;
        }

        void saveChanges() {
            std::vector<T> &entities{getAll()};

            for (Change<T> &change: m_changeTracker) {
                switch (change.type) {
                    case cgram::add:
                        entities.push_back(change.value.getId());
                        break;
                    case cgram::remove: {
                        const auto entity{find(change.value.getId())};
                        entities.erase(entity);
                    }
                        break;
                    case cgram::update: {
                        const auto entity{find(change.value.getId())};
                        entities.erase(entity);
                        entities.push_back(change.value);
                    }
                        break;
                    case none:
                    default:
                        throw std::invalid_argument("Change was not implemented");
                }
            }

            m_changeTracker.clear();
        }
    };

    class Entity {
    private:
        long m_id{};

    public:
        explicit Entity(long id) : m_id{id} {
        }

        [[nodiscard]] long getId() const {
            return m_id;
        }
    };

    class User : public Entity {
    private:
        std::string_view m_userName{};
        std::string_view m_password{};
    public:
        explicit User(long id, std::string_view userName, std::string_view password)
                : Entity(id), m_userName{userName}, m_password{password} {
        }

        [[nodiscard]] std::string_view getUserName() const {
            return m_userName;
        }

        [[nodiscard]] std::string_view getPassword() const {
            return m_password;
        }
    };

    class Participant : public Entity {
    private:
        long m_userId{};
        long m_chatId{};
        bool m_canWrite{};
    public:
        explicit Participant(long id, long userId, long chatId, bool canWrite)
                : Entity(id), m_userId{userId}, m_chatId{chatId}, m_canWrite{canWrite} {
        }

        [[nodiscard]] long getUserId() const {
            return m_userId;
        }

        [[nodiscard]] long getChatId() const {
            return m_chatId;
        }

        [[nodiscard]] long canWrite() const {
            return m_canWrite;
        }
    };
    
    class Message : public Entity {
    private:
        long m_userId{};
        long m_chatId{};
        std::string_view m_text{};
    public:
        explicit Message(long id, long userId, long chatId, std::string_view text)
                : Entity(id), m_userId{userId}, m_chatId{chatId}, m_text{text} {
        }

        [[nodiscard]] long getUserId() const {
            return m_userId;
        }

        [[nodiscard]] long getChatId() const {
            return m_chatId;
        }

        [[nodiscard]] std::string_view getText() const {
            return m_text;
        }
    };

    class Chat : public Entity {
    private:
        std::string_view m_name{};
    public:
        explicit Chat(long id, std::string_view name) : Entity(id), m_name{name} {
        }

        [[nodiscard]] std::string_view getName() const {
            return m_name;
        }
    };

    class UserRepository : public Repository<User> {
    public:
        explicit UserRepository(const std::vector<User> &users) : Repository<User>{users} {
        }

        std::vector<User>::iterator getByUserName(std::string_view userName) {
            std::vector<User> &entities{getAll()};
            return std::find_if(entities.begin(), entities.end(), [userName](const User &item) {
                return item.getUserName() == userName;
            });
        }
    };

    class ParticipantRepository : public Repository<Participant> {
    public:
        explicit ParticipantRepository(const std::vector<Participant> &participants) : Repository<Participant>{
                participants} {
        }

        std::vector<long> getChatsIds(long userId) {
            const std::vector<Participant> &participants{getAll()};

            const std::vector<Participant> filteredByUserId{
                    where<Participant>(participants, [userId](const Participant &participant) {
                        return participant.getUserId() == userId;
                    })};

            return select<Participant, long>(filteredByUserId, [](const Participant &participant) {
                return participant.getChatId();
            });
        }
    };

    class ChatRepository : public Repository<Chat> {
    public:
        explicit ChatRepository(const std::vector<Chat> &chats) : Repository<Chat>{chats} {
        }
    };

    class MessageRepository : public Repository<Message> {
    public:
        explicit MessageRepository(const std::vector<Message> &messages) : Repository<Message>{messages} {
        }

        std::vector<Message> getLastMessages(std::vector<long> &chatIds) {
            const std::vector<Message> &messages{getAll()};

            const std::vector<Message> filteredByChatIds{where<Message>(messages, [&chatIds](const Message &message) {
                return std::any_of(chatIds.begin(), chatIds.end(), [&message](long chatId) {
                    return message.getChatId() == chatId;
                });
            })};

            std::vector<Message> lastMessages{};
            for (const Message &message: filteredByChatIds) {
                const std::vector<Message> filteredByChatId{
                        where<Message>(filteredByChatIds, [&message](const Message &item) {
                            return item.getChatId() == message.getChatId();
                        })};

                const Message &maxIdMessage{*std::max_element(filteredByChatId.begin(), filteredByChatId.end(),
                                                              [](const Message &first, const Message &second) {
                                                                  return first.getId() < second.getId();
                                                              })};

                if (maxIdMessage.getId() > message.getId()) {
                    lastMessages.push_back(maxIdMessage);
                }
            }

            return lastMessages;
        }
    };

    static UserRepository s_usersRepository{{
                                                    User{1, "admin", "admin"}
                                            }};

    static ParticipantRepository s_participantsRepository{{
                                                                  Participant{1, 1, 1, true},
                                                                  Participant{2, 1, 2, true},
                                                          }};

    static MessageRepository s_messagesRepository{{
                                                          Message{1, 1, 1, "hi"},
                                                          Message{2, 1, 1, "hi 2"},

                                                          Message{3, 1, 2, "hi 3"},
                                                          Message{4, 1, 2,
                                                                  "really really really really really really long message"},

                                                  }};

    static ChatRepository s_chatsRepository{{
                                                    Chat{1, "first chat"},
                                                    Chat{2, "second chat"}
                                            }};

    std::string getString(std::string_view ask) {
        std::cout << ask;
        std::string input{};
        std::getline(std::cin >> std::ws, input);
        return input;
    }

    User *authenticate() {
        while (true) {
            const std::string_view userName{getString("Please, login.\nEnter username:")};

            const std::vector<User>::iterator user{s_usersRepository.getByUserName(userName)};

            if (user == s_usersRepository.end()) {
                std::cout << "User with such username was not found\n";
                continue;
            }

            const std::string_view password{getString("Enter password:")};

            if (user->getPassword() != password) {
                std::cout << "Password is incorrect\n";
                continue;
            }

            return user.base();
        }
    }

    namespace view {
        std::string_view setColor(HANDLE hConsole, int wAttributes) {
            SetConsoleTextAttribute(hConsole, wAttributes);
            return "";
        }

        std::string_view setBlueColor(HANDLE hConsole) {
            return setColor(hConsole, 1);
        }

        std::string_view setBlackColor(HANDLE hConsole) {
            return setColor(hConsole, 0);
        }

        std::string_view setDarkYellowColor(HANDLE hConsole) {
            return setColor(hConsole, 6);
        }

        std::string_view setGrayColor(HANDLE hConsole) {
            return setColor(hConsole, 8);
        }

        std::string_view setPurple(HANDLE hConsole) {
            return setColor(hConsole, 5);
        }
    }

    static std::string_view s_chatSeparator{"------------------------------------\n"};
    
    void showHomePage(const User *user) {
        std::vector<long> chatIds{s_participantsRepository.getChatsIds(user->getId())};
        std::vector<Chat> chats{s_chatsRepository.get(chatIds)};
        std::vector<Message> messages{s_messagesRepository.getLastMessages(chatIds)};

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        for (const Chat &chat: chats) {
            const std::vector<Message>::iterator message{
                    std::find_if(messages.begin(), messages.end(), [&chat](const Message &item) {
                        return chat.getId() == item.getChatId();
                    })};

            std::cout
                    << view::setGrayColor(hConsole) << s_chatSeparator
                    << "--- " << view::setBlueColor(hConsole) << chat.getName() << '\n';

            if (message != s_messagesRepository.end()) {

                std::cout
                        << view::setGrayColor(hConsole) << '-' << view::setPurple(hConsole) << chat.getId()
                        << view::setGrayColor(hConsole) << "- "
                        << view::setDarkYellowColor(hConsole) << message->getText().substr(0, s_chatSeparator.size() - 5) << '\n'
                        << view::setGrayColor(hConsole);
            }
        }

        std::cout << s_chatSeparator;
    }
}

int main() {
    const cgram::User *currentUser{cgram::authenticate()};
    cgram::showHomePage(currentUser);
    return EXIT_SUCCESS;
}