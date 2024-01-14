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
    class DbSet {
    private:
        std::vector<T> m_entities{};
        std::vector<Change<T>> m_changeTracker{};

    public:
        explicit DbSet(const std::vector<T> &entities) : m_entities{entities} {
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
                        std::format("User with id({}) was not found", value.id));
            }

            return entity;
        }

        friend class Database;
    };

    struct User {
        long id{};
        std::string_view userName{};
        std::string_view password{};
    };

    class Database {
    public:
        DbSet<User> users{{
                                  {1, "admin", "admin"}
                          }};

        void saveChanges() {
            for (Change<User> &change: users.m_changeTracker) {
                switch (change.type) {
                    case add:
                        users.m_entities.push_back(change.value);
                        break;
                    case remove: {
                        const auto user{users.find(change.value)};
                        users.m_entities.erase(user);
                    }
                        break;
                    case update: {
                        const auto user{users.find(change.value)};
                        if (!change.value.userName.empty()) {
                            user->userName = change.value.userName;
                        }

                        if (!change.value.password.empty()) {
                            user->password = change.value.password;
                        }
                    }
                        break;
                    case none:
                    default:
                        throw std::invalid_argument("Change was not implemented");
                }
            }

            users.m_changeTracker.clear();
        }
    };
}


int main() {
    cgram::Database database{};

    database.users.add({2, "newUser", "123"});

    database.saveChanges();

    database.users.remove({2});

    database.saveChanges();

    database.users.update({1, "newAdmin"});

    database.saveChanges();

    return 0;
}
