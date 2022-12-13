#pragma once

#include <engine/ecs/component_storage.hpp>

#include <iostream>

namespace engine::ecs
{
class View final
{
public:
    View() = delete;
    View(ComponentStorage& storage) : m_componentStorage{storage} {}

    template <typename T, typename... Ts>
    std::vector<std::tuple<T&, Ts&...>> get()
    {
        // TODO: It's a simple implementation
        // At least, you need to add caching
        auto firstContainer = m_componentStorage.getContainer<T>();

        std::vector<Entity> entities = firstContainer->getEntities();
        std::vector<Entity> matchingEntities{};

        for (auto e : entities)
        {
            bool isSuitable = {m_componentStorage.getContainer<Ts>()->has(e)...};

            if (isSuitable)
            {
                matchingEntities.push_back(e);
            }
        }

        std::vector<std::tuple<T&, Ts&...>> view{};

        for (auto e : matchingEntities)
        {
            view.push_back(std::tie(m_componentStorage.getContainer<T>()->get(e), m_componentStorage.getContainer<Ts>()->get(e)...));
        }

        return view;
    }

private:
    ComponentStorage& m_componentStorage;
};
} // namespace engine::ecs
