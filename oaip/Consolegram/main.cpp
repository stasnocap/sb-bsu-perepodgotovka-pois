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

    class Database {
    public:
        DbSet<User> users{{
                                  {1, "admin", "admin"}
                          }};

        void saveChanges() {
            users.saveChanges();
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
