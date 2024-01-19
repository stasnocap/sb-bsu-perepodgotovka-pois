#include <iostream>
#include <vector>
#include <algorithm>
#include <format>

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

    template<typename T>
    class Repository {
    private:
        std::vector<T> m_entities{};
        std::vector<Change<T>> m_changeTracker{};

    public:
        explicit Repository(const std::vector<T> &entities) : m_entities{entities} {
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

        auto find(const T &value) {
            auto entity{std::find_if(m_entities.begin(), m_entities.end(), [&value](const T &element) {
                return element.id == value.id;
            })};

            if (entity == m_entities.end()) {
                throw std::invalid_argument(
                        std::format("{} with id({}) was not found", typeid(T).name(), value.id));
            }

            return entity;
        }

        auto find(auto predicate) {
            return predicate(m_entities);
        }

        void saveChanges() {
            for (Change<T> &change: m_changeTracker) {
                switch (change.type) {
                    case cgram::add:
                        m_entities.push_back(change.value);
                        break;
                    case cgram::remove: {
                        const auto entity{find(change.value)};
                        m_entities.erase(entity);
                    }
                        break;
                    case cgram::update: {
                        const auto entity{find(change.value)};
                        m_entities.erase(entity);
                        m_entities.push_back(change.value);
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

    struct User {
        long id{};
        std::string_view userName{};
        std::string_view password{};
    };

    std::string getString(std::string_view ask) {
        std::cout << ask;
        std::string input{};
        std::getline(std::cin >> std::ws, input);
        return input;
    }

    static Repository<User> users{{
                                          {1, "admin", "admin"}
                                  }};

    void authenticate() {
        while (true) {
            std::string userName{getString("Please, login.\nEnter username:")};

            auto user{users.find([&](const std::vector<User> &users) {
                auto entity{std::find_if(users.begin(), users.end(), [&](const User &user) {
                    return userName == user.userName;
                })};

                if (entity == users.end()) {
                    return User{};
                }

                return *entity;
            })};

            if (user.id <= 0) {
                std::cout << "User with such username was not found\n";
                continue;
            }

            std::string password{getString("Enter password:")};

            if (user.password != password) {
                std::cout << "Password is incorrect\n";
                continue;
            }

            break;
        }
    }
}

int main() {
    cgram::authenticate();
    return EXIT_SUCCESS;
}
