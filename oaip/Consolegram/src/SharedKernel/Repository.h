#pragma once

#include <algorithm>
#include <format>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>
#include "../SharedKernel/Change.h"
#include "../SharedKernel/Common.h"

namespace Consolegram::SharedKernel
{
    template <typename T>
    class Repository
    {
        std::vector<T> _cachedEntities{};
        std::vector<Change<T>> _changeTracker{};
        typename std::vector<T>::iterator _end{};
        std::string _fileName{};
        std::function<std::vector<T>(std::ifstream &)> _fileReader{};

    public:
        explicit Repository(std::string fileName,
                            std::function<std::vector<T>(std::ifstream &)> fileReader)
            : _fileName{std::move(fileName)}, _fileReader{std::move(fileReader)}
        {
        }

        typename std::vector<T>::iterator End()
        {
            return _end;
        }

        void Add(const T& entity)
        {
            _changeTracker.push_back({ChangeType::Add, entity});
        }

        void Remove(const T& entity)
        {
            _changeTracker.push_back({ChangeType::Remove, entity});
        }

        void Update(const T& entity)
        {
            _changeTracker.push_back({ChangeType::Update, entity});
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
            // ReSharper disable once CppRedundantTemplateKeyword
            return SharedKernel::template Where<T>(entities, [&ids](const T& entity)
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
                case ChangeType::Add:
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
                case ChangeType::Remove:
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
                case ChangeType::Update:
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
                case ChangeType::None:
                default:
                    throw std::invalid_argument("Change was not implemented");
                }
            }

            _changeTracker.clear();
        }
    };
}