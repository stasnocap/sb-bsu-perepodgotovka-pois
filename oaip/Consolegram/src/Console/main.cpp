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

namespace cgram
{
    constexpr std::string_view environment_key{"--environment"};
    constexpr std::string_view development_environment{"development"};
    constexpr std::string_view production_environment{"production"};
    constexpr std::string_view appsettings_file_name_without_extension{"appsettings"};
    constexpr std::string_view chat_separator{"------------------------------------\n"};

    constexpr int max_chat_name_length{30};
    constexpr int max_message_text_length{100};

    enum change_type
    {
        none,
        add,
        remove,
        update,
    };

    template <typename T>
    struct change
    {
        change_type type{};
        T value{};
    };


    template <typename TEntity, typename TResult>
    std::vector<TResult> select(const std::vector<TEntity>& entities,
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
    std::vector<TEntity> where(const std::vector<TEntity>& entities,
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

    class entity
    {
        long id_{};

    public:
        explicit entity(const long id) : id_{id}
        {
        }

        long get_id() const
        {
            return id_;
        }
    };

    class user : public entity
    {
        std::string name_{};
        std::string password_{};

    public:
        explicit user(const long id, std::string user_name, std::string password)
            : entity(id), name_{std::move(user_name)}, password_{std::move(password)}
        {
        }

        [[nodiscard]] std::string_view get_user_name() const
        {
            return name_;
        }

        [[nodiscard]] std::string_view get_password() const
        {
            return password_;
        }
    };

    class participant : public entity
    {
        long user_id_{};
        long chat_id_{};
        bool can_write_{};

    public:
        explicit participant(const long id, const long user_id, const long chat_id, const bool can_write)
            : entity(id), user_id_{user_id}, chat_id_{chat_id}, can_write_{can_write}
        {
        }

        [[nodiscard]] long get_user_id() const
        {
            return user_id_;
        }

        [[nodiscard]] long get_chat_id() const
        {
            return chat_id_;
        }

        [[nodiscard]] long can_write() const
        {
            return can_write_;
        }
    };

    class message : public entity
    {
        long user_id_{};
        long chat_id_{};
        std::string text_{};

    public:
        explicit message(const long id, const long user_id, const long chat_id, std::string text)
            : entity(id), user_id_{user_id}, chat_id_{chat_id}, text_{std::move(text)}
        {
        }

        [[nodiscard]] long get_user_id() const
        {
            return user_id_;
        }

        [[nodiscard]] long get_chat_id() const
        {
            return chat_id_;
        }

        [[nodiscard]] std::string_view get_text() const
        {
            return text_;
        }
    };

    class chat : public entity
    {
        std::string name_{};

    public:
        explicit chat(const long id, std::string name) : entity(id), name_{std::move(name)}
        {
        }

        [[nodiscard]] std::string_view get_name() const
        {
            return name_;
        }
    };

    template <typename T>
    class repository
    {
        std::vector<T> cached_entities_{};
        std::vector<change<T>> change_tracker_{};
        typename std::vector<T>::iterator end_{};
        std::string file_name_{};
        std::function<std::vector<T>(std::ifstream&)> file_reader_{};

    public:
        explicit repository(std::string file_name,
                            std::function<std::vector<T>(std::ifstream&)> file_reader)
            : file_name_{std::move(file_name)}, file_reader_{std::move(file_reader)}
        {
        }

        typename std::vector<T>::iterator end()
        {
            return end_;
        }

        void add(const T& entity)
        {
            change_tracker_.push_back({cgram::add, entity});
        }

        void remove(const T& entity)
        {
            change_tracker_.push_back({cgram::remove, entity});
        }

        void update(const T& entity)
        {
            change_tracker_.push_back({cgram::update, entity});
        }

        auto get(long id) const
        {
            const std::vector<T>& entities{get_all()};
            return std::find_if(entities.begin(), entities.end(), [&id](const T& item)
            {
                return item.getId() == id;
            });
        }

        std::vector<T> get(std::vector<long>& ids)
        {
            const std::vector<T>& entities{get_all()};
            return where<T>(entities, [&ids](const T& entity)
            {
                return std::any_of(ids.begin(), ids.end(), [&entity](long id)
                {
                    return entity.get_id() == id;
                });
            });
        }

        std::vector<T>& get_all()
        {
            if (!cached_entities_.empty())
            {
                return cached_entities_;
            }

            std::ifstream file_stream{file_name_.data()};

            if (!file_stream.is_open())
            {
                throw std::invalid_argument(std::format("The {} cannot be opened!", file_name_));
            }

            std::vector<T> entities{file_reader_(file_stream)};

            file_stream.close();

            cached_entities_ = entities;
            end_ = cached_entities_.end();

            return cached_entities_;
        }

        void save_changes()
        {
            std::vector<T>& entities{get_all()};

            for (change<T>& change : change_tracker_)
            {
                if (change.value.get_id() < 1)
                {
                    throw std::invalid_argument("Id can't be zero or below");
                }

                switch (change.type)
                {
                case cgram::add:
                    if (std::any_of(entities.begin(), entities.end(), [&change](const T& item)
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
                case cgram::remove:
                    {
                        const auto entity{get(change.value.getId())};
                        if (entity == entities.end())
                        {
                            throw std::invalid_argument(std::format("{} with id({}) was not found",
                                                                    typeid(T).name(),
                                                                    change.value.getId()));
                        }

                        entities.erase(entity);
                    }
                    break;
                case cgram::update:
                    {
                        const auto entity{get(change.value.getId())};
                        if (entity == entities.end())
                        {
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

            change_tracker_.clear();
        }
    };

    namespace common
    {
        std::string get_string(const std::string_view ask)
        {
            std::cout << ask;
            std::string input{};
            std::getline(std::cin >> std::ws, input);
            return input;
        }

        template <typename T>
        std::string to_lower(T& data)
        {
            std::string lower{data};
            std::transform(lower.begin(), lower.end(), lower.begin(),
                           [](const unsigned char c) { return std::tolower(c); });
            return lower;
        }
    }

    class config
    {
        std::map<std::string, std::string> settings_{};
        bool is_development_{};
        bool is_production_{};

        void read_settings(std::string_view appsettings_file_name, bool isRequired)
        {
            std::ifstream i_file_stream(appsettings_file_name.data());

            if (!i_file_stream.is_open())
            {
                if (isRequired)
                {
                    throw std::invalid_argument(std::format("The {} cannot be opened!", appsettings_file_name));
                }

                return;
            }

            i_file_stream.get();
            i_file_stream.get();
            i_file_stream.get();

            std::string line{};
            while (std::getline(i_file_stream, line))
            {
                std::istringstream i_string_stream(line);

                std::string key{};
                if (!std::getline(i_string_stream, key, '='))
                {
                    break;
                }

                std::string value{};
                if (!std::getline(i_string_stream, value))
                {
                    break;
                }

                settings_[key] = value;
            }
        }

        std::string get_environment(const int argc, char* argv[])
        {
            std::string environment{};
            for (int i = 1; i < argc; ++i)
            {
                const std::string lower_arg{common::to_lower(argv[i])};
                if (lower_arg == environment_key && i + 1 < argc)
                {
                    const std::string next_lower_arg{common::to_lower(argv[i + 1])};
                    if (next_lower_arg == production_environment)
                    {
                        environment = production_environment;
                        is_development_ = false;
                        is_production_ = true;
                        break;
                    }
                }
            }

            if (environment.empty())
            {
                environment = development_environment;
                is_development_ = true;
                is_production_ = false;
            }

            return environment;
        }

    public:
        std::string operator[](const std::string& key) const
        {
            return settings_.at(key);
        }

        [[nodiscard]] bool isDevelopment() const
        {
            return is_development_;
        }

        [[nodiscard]] bool isProduction() const
        {
            return is_production_;
        }

        void init(const int argc, char* argv[])
        {
            std::string environment(get_environment(argc, argv));
            environment[0] = static_cast<char>(std::toupper(environment[0]));
            read_settings(std::format("{}.txt", appsettings_file_name_without_extension), true);
            read_settings(std::format("{}.{}.txt", appsettings_file_name_without_extension, environment), false);
        }
    };

    class user_repository : public repository<user>
    {
    public:
        explicit user_repository(const config& config) : repository{
            config["UsersFileRelativePath"],
            [](std::ifstream& file_stream)
            {
                std::vector<user> users{};

                long id{};
                std::string user_name{};
                std::string password{};

                while (!file_stream.eof())
                {
                    file_stream >> id;
                    file_stream >> user_name;
                    file_stream >> password;

                    users.emplace_back(id, user_name,
                                       password);
                }

                return users;
            }
        }
        {
            auto m{config["UsersFileRelativePath"]};
        }

        std::vector<user>::iterator get_by_user_name(std::string_view user_name)
        {
            std::vector<user>& entities{get_all()};
            return std::ranges::find_if(entities, [user_name](const user& item)
            {
                return item.get_user_name() == user_name;
            });
        }
    };

    class participant_repository : public repository<participant>
    {
    public:
        explicit participant_repository(const config& config) : repository{
            config["ParticipantsFileRelativePath"], [](std::ifstream& fileStream)
            {
                std::vector<participant> participants{};

                long id{};
                long user_id{};
                long chat_id{};
                std::string canWrite{};

                while (!fileStream.eof())
                {
                    fileStream >> id;
                    fileStream >> user_id;
                    fileStream >> chat_id;
                    fileStream >> canWrite;

                    participants.emplace_back(id, user_id, chat_id, canWrite == "true");
                }

                return participants;
            }
        }
        {
        }

        std::vector<long> get_chats_ids(long user_id)
        {
            const std::vector<participant>& participants{get_all()};

            const std::vector filtered_by_user_id{
                where<participant>(participants, [user_id](const participant& participant)
                {
                    return participant.get_user_id() == user_id;
                })
            };

            return select<participant, long>(filtered_by_user_id, [](const participant& participant)
            {
                return participant.get_chat_id();
            });
        }
    };

    class chat_repository : public repository<chat>
    {
    public:
        explicit chat_repository(const config& config) : repository{
            config["ChatsFileRelativePath"], [](std::ifstream& file_stream)
            {
                std::vector<chat> chats{};

                long id{};
                char name[max_chat_name_length]{};

                while (!file_stream.eof())
                {
                    file_stream >> id;

                    file_stream.get();
                    file_stream.getline(name, max_chat_name_length, '\n');

                    chats.emplace_back(id, name);
                }

                return chats;
            }
        }
        {
        }
    };

    class message_repository : public repository<message>
    {
    public:
        explicit message_repository(const config& config) : repository{
            config["MessagesFileRelativePath"],
            [](std::ifstream& file_stream)
            {
                std::vector<message> messages{};

                long id{};
                long user_id{};
                long chat_id{};
                char text[max_message_text_length]{};

                while (!file_stream.eof())
                {
                    file_stream >> id;
                    file_stream >> user_id;
                    file_stream >> chat_id;

                    file_stream.get();
                    file_stream.getline(text, max_message_text_length,
                                        '\n');

                    messages.emplace_back(id, user_id, chat_id, text);
                }

                return messages;
            }
        }
        {
        }

        std::vector<message> get_last_messages(std::vector<long>& chat_ids)
        {
            const std::vector<message>& messages{get_all()};

            const std::vector filtered_by_chat_ids{
                where<message>(messages, [&chat_ids](const message& message)
                {
                    return std::ranges::any_of(chat_ids, [&message](const long chat_id)
                    {
                        return message.get_chat_id() == chat_id;
                    });
                })
            };

            std::vector<message> last_messages{};
            for (const message& msg : filtered_by_chat_ids)
            {
                const std::vector filtered_by_chat_id{
                    where<message>(filtered_by_chat_ids, [&msg](const message& item)
                    {
                        return msg.get_chat_id() == item.get_chat_id();
                    })
                };

                if (const message& max_id_message{
                    *std::ranges::max_element(filtered_by_chat_id,
                                              [](const message& first, const message& second)
                                              {
                                                  return first.get_id() < second.get_id();
                                              })
                }; max_id_message.get_id() > msg.get_id())
                {
                    last_messages.push_back(max_id_message);
                }
            }

            return last_messages;
        }
    };

    user* authenticate(user_repository& users_repository)
    {
        while (true)
        {
            const std::string user_name{common::get_string("Please, login.\nEnter username:")};

            const auto user{users_repository.get_by_user_name(user_name)};

            if (user == users_repository.end())
            {
                std::cout << "User with such username was not found\n";
                continue;
            }

            const std::string password{common::get_string("Enter password:")};

            if (user->get_password() != password)
            {
                std::cout << "Password is incorrect\n";
                continue;
            }

            return user._Ptr;
        }
    }

    namespace cview
    {
        std::string_view set_color(const HANDLE h_console, const WORD w_attributes)
        {
            SetConsoleTextAttribute(h_console, w_attributes);
            return "";
        }

        std::string_view set_blue_color(const HANDLE h_console)
        {
            return set_color(h_console, 1);
        }

        std::string_view set_black_color(const HANDLE h_console)
        {
            return set_color(h_console, 0);
        }

        std::string_view set_dark_yellow_color(const HANDLE h_console)
        {
            return set_color(h_console, 6);
        }

        std::string_view set_gray_color(const HANDLE h_console)
        {
            return set_color(h_console, 8);
        }

        std::string_view set_purple_color(const HANDLE h_console)
        {
            return set_color(h_console, 5);
        }
    }

    void show_home_page(
        const user* user,
        participant_repository& participant_repository,
        chat_repository& chat_repository,
        message_repository& message_repository
    )
    {
        std::vector chat_ids{participant_repository.get_chats_ids(user->get_id())};
        const std::vector chats{chat_repository.get(chat_ids)};
        std::vector messages{message_repository.get_last_messages(chat_ids)};

        const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

        for (const chat& chat : chats)
        {
            std::vector<message>::iterator msg{
                std::ranges::find_if(messages, [&chat](const message& item)
                {
                    return chat.get_id() == item.get_chat_id();
                })
            };

            std::cout
                << cview::set_gray_color(h_console) << chat_separator << "--- "
                << cview::set_blue_color(h_console) << chat.get_name() << '\n';

            if (msg != messages.end())
            {
                std::cout
                    << cview::set_gray_color(h_console) << '-'
                    << cview::set_purple_color(h_console) << chat.get_id()
                    << cview::set_gray_color(h_console) << "- "
                    << cview::set_dark_yellow_color(h_console)
                    << msg->get_text().substr(0, chat_separator.size() - 5) << '\n';
            }
        }

        std::cout << cview::set_gray_color(h_console) << chat_separator;
    }
}

int main(int argc, char* argv[])
{
    cgram::config config{};
    config.init(argc, argv);

    cgram::user_repository user_repository{config};
    cgram::participant_repository participant_repository{config};
    cgram::message_repository message_repository{config};
    cgram::chat_repository chat_repository{config};

    const cgram::user* current_user{authenticate(user_repository)};
    show_home_page(current_user, participant_repository, chat_repository, message_repository);
    return EXIT_SUCCESS;
}
