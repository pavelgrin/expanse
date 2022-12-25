#pragma once

#include <engine/ecs/component_storage.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{

class ViewManager final
{
public:
    ViewManager() = delete;
    ViewManager(ComponentStorage& storage) : m_componentStorage{storage} {}

    template <typename... Ts>
    std::vector<std::tuple<Ts&...>> get()
    {
        // TODO: Implement caching

        auto minEntityCount{m_componentStorage.getContainer<Entity>()->size()};

        for (auto count : {m_componentStorage.getContainer<Ts>()->size()...})
        {
            if (minEntityCount > count)
            {
                minEntityCount = count;
            }
        }

        std::vector<Entity> entities{getEntities<Ts...>(minEntityCount)};

        std::vector<Entity> matchingEntities{};
        matchingEntities.reserve(entities.size());

        for (auto e : entities)
        {
            bool isSuitable = (m_componentStorage.getContainer<Ts>()->has(e) && ...);

            if (isSuitable)
            {
                matchingEntities.push_back(e);
            }
        }

        std::vector<std::tuple<Ts&...>> view{};

        for (auto e : matchingEntities)
        {
            view.push_back(std::tie(m_componentStorage.getContainer<Ts>()->get(e)...));
        }

        return view;
    }

private:
    ComponentStorage& m_componentStorage;

    template <typename T = Entity, typename... Ts>
    std::vector<Entity> getEntities(size_t entityCount)
    {
        auto container = m_componentStorage.getContainer<T>();

        if (container->size() == entityCount)
        {
            return container->getEntities();
        }

        return getEntities<Ts...>(entityCount);
    }
};

} // namespace engine::ecs
