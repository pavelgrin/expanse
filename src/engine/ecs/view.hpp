#pragma once

#include <engine/ecs/component_storage.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{

class IView
{
public:
    virtual ~IView() = default;

    virtual void update(Entity) = 0;
};

template <typename... Ts>
class View final : public IView
{
    ComponentStorage& m_componentStorage;

    std::vector<std::tuple<Ts&...>> m_view{};
    std::vector<Entity> m_matchedEntities{};

public:
    View() = delete;
    View(ComponentStorage& storage) : m_componentStorage{storage}
    {
        auto minEntityCount{m_componentStorage.getContainer<Entity>()->size()};

        for (const auto count : {m_componentStorage.getContainer<Ts>()->size()...})
        {
            if (minEntityCount > count)
            {
                minEntityCount = count;
            }
        }

        std::vector<Entity> unverifiedEntities{getEntities<Ts...>(minEntityCount)};

        m_matchedEntities.reserve(unverifiedEntities.size());

        for (const auto e : unverifiedEntities)
        {
            bool isSuitable = (m_componentStorage.getContainer<Ts>()->has(e) && ...);

            if (isSuitable)
            {
                m_matchedEntities.push_back(e);
            }
        }

        for (const auto e : m_matchedEntities)
        {
            m_view.push_back(std::tie(m_componentStorage.getContainer<Ts>()->get(e)...));
        }
    }

    std::vector<std::tuple<Ts&...>> get()
    {
        return m_view;
    }

private:
    template <typename T = Entity, typename... Rest>
    std::vector<Entity> getEntities(size_t entityCount)
    {
        const auto& container = m_componentStorage.getContainer<T>();

        if (container->size() == entityCount)
        {
            return container->getEntities();
        }

        return getEntities<Rest...>(entityCount);
    }

    void update(Entity e) override
    {
        const auto it    = std::find(m_matchedEntities.begin(), m_matchedEntities.end(), e);
        const auto index = std::distance(m_matchedEntities.begin(), it);

        const bool isSuitable = (m_componentStorage.getContainer<Ts>()->has(e) && ...);
        const bool hasEntity  = it != m_matchedEntities.end();

        if (isSuitable && !hasEntity)
        {
            m_matchedEntities.push_back(e);
            m_view.push_back(std::tie(m_componentStorage.getContainer<Ts>()->get(e)...));
        }
        else if (!isSuitable && hasEntity)
        {
            m_matchedEntities.erase(it);
            m_view.erase(m_view.begin() + index);
        }
    }
};

} // namespace engine::ecs
