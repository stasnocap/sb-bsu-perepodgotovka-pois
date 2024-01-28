#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <format>
#include <functional>
#include <windows.h>
#include <fstream>

namespace cgram {
    constexpr int g_max_chat_name_length{30};
    constexpr int g_max_message_text_length{100};

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
        std::string m_userName{};
        std::string m_password{};
    public:
        explicit User(long id, std::string userName, std::string password)
                : Entity(id), m_userName{std::move(userName)}, m_password{std::move(password)} {
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
        std::string m_text{};
    public:
        explicit Message(long id, long userId, long chatId, std::string text)
                : Entity(id), m_userId{userId}, m_chatId{chatId}, m_text{std::move(text)} {
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
        std::string m_name{};
    public:
        explicit Chat(long id, std::string name) : Entity(id), m_name{std::move(name)} {
        }

        [[nodiscard]] std::string_view getName() const {
            return m_name;
        }
    };

    template<typename T>
    class Repository {
    private:
        std::vector<T> m_cached_entities{};
        std::vector<Change<T>> m_changeTracker{};
        std::vector<T>::iterator m_end{};
        std::string_view m_fileName{};
        std::function<std::vector<T>(std::ifstream &)> m_fileReader{};

    public:
        explicit Repository(std::string_view fileName,
                            std::function<std::vector<T>(std::ifstream &)> fileReader)
                : m_fileName{fileName}, m_fileReader{std::move(fileReader)} {
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

        auto get(long id) {
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
            if (!m_cached_entities.empty()) {
                return m_cached_entities;
            }

            std::ifstream fileStream{m_fileName.data()};

            if (!fileStream.is_open()) {
                throw std::invalid_argument(std::format("The {} cannot be opened!", m_fileName));
            }

            std::vector<T> entities{m_fileReader(fileStream)};

            fileStream.close();

            m_cached_entities = entities;
            m_end = m_cached_entities.end();

            return m_cached_entities;
        }

        void saveChanges() {
            std::vector<T> &entities{getAll()};

            for (Change<T> &change: m_changeTracker) {
                if (change.value.getId() < 1){
                    throw std::invalid_argument("Id can't be zero or below");
                }
                
                switch (change.type) {
                    case cgram::add:
                        if (std::any_of(entities.begin(), entities.end(), [&change](const T &item) {
                            return change.value.getId() == item.getId();
                        })) {
                            throw std::invalid_argument(std::format("{} with id({}) already exists",
                                                                    typeid(T).name(),
                                                                    change.value.getId()));
                        }

                        entities.push_back(change.value);
                        break;
                    case cgram::remove: {
                        const auto entity{get(change.value.getId())};
                        if (entity == entities.end()) {
                            throw std::invalid_argument(std::format("{} with id({}) was not found",
                                                                    typeid(T).name(),
                                                                    change.value.getId()));
                        }

                        entities.erase(entity);
                    }
                        break;
                    case cgram::update: {
                        const auto entity{get(change.value.getId())};
                        if (entity == entities.end()) {
                            throw std::invalid_argument(std::format("{} with id({}) was not found",
                                                                    typeid(T).name(),
                                                                    change.value.getId()));
                        }

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

    class UserRepository : public Repository<User> {
    public:
        explicit UserRepository() : Repository<User>{"Users.txt",
                                                     [](std::ifstream &fileStream) {
                                                         std::vector<User> users{};

                                                         long id{};
                                                         std::string userName{};
                                                         std::string password{};

                                                         while (!fileStream.eof()) {
                                                             fileStream >> id;
                                                             fileStream >> userName;
                                                             fileStream >> password;

                                                             users.emplace_back(id, userName,
                                                                                password);
                                                         }

                                                         return users;
                                                     }} {
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
        explicit ParticipantRepository() : Repository<Participant>{
                "Participants.txt", [](std::ifstream &fileStream) {
                    std::vector<Participant> participants{};

                    long id{};
                    long userId{};
                    long chatId{};
                    std::string canWrite{};

                    while (!fileStream.eof()) {
                        fileStream >> id;
                        fileStream >> userId;
                        fileStream >> chatId;
                        fileStream >> canWrite;

                        participants.emplace_back(id, userId, chatId, canWrite == "true");
                    }

                    return participants;
                }} {
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
        explicit ChatRepository() : Repository<Chat>{"Chats.txt", [](std::ifstream &fileStream) {
            std::vector<Chat> chats{};

            long id{};
            char name[g_max_chat_name_length]{};

            while (!fileStream.eof()) {
                fileStream >> id;

                fileStream.get();
                fileStream.getline(name, g_max_chat_name_length, '\n');

                chats.emplace_back(id, name);
            }

            return chats;
        }} {
        }
    };

    class MessageRepository : public Repository<Message> {
    public:
        explicit MessageRepository() : Repository<Message>{"Messages.txt",
                                                           [](std::ifstream &fileStream) {
                                                               std::vector<Message> messages{};

                                                               long id{};
                                                               long userId{};
                                                               long chatId{};
                                                               char text[g_max_message_text_length]{};

                                                               while (!fileStream.eof()) {
                                                                   fileStream >> id;
                                                                   fileStream >> userId;
                                                                   fileStream >> chatId;

                                                                   fileStream.get();
                                                                   fileStream.getline(text, g_max_message_text_length,
                                                                                      '\n');

                                                                   messages.emplace_back(id, userId, chatId, text);
                                                               }

                                                               return messages;
                                                           }} {
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

    static UserRepository s_usersRepository{};

    static ParticipantRepository s_participantsRepository{};

    static MessageRepository s_messagesRepository{};

    static ChatRepository s_chatsRepository{};

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

        std::string_view setPurpleColor(HANDLE hConsole) {
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
                        << view::setGrayColor(hConsole) << '-' << view::setPurpleColor(hConsole) << chat.getId()
                        << view::setGrayColor(hConsole) << "- "
                        << view::setDarkYellowColor(hConsole)
                        << message->getText().substr(0, s_chatSeparator.size() - 5) << '\n'
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