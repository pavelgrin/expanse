#pragma once

#include <engine/ecs/component_storage.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{

class IView
{
};

template <typename... Ts>
class View final : public IView
{
public:
    View() = delete;
    View(ComponentStorage& storage) : m_componentStorage{storage}
    {
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

        for (auto e : matchingEntities)
        {
            m_view.push_back(std::tie(m_componentStorage.getContainer<Ts>()->get(e)...));
        }
    }

    std::vector<std::tuple<Ts&...>> get()
    {
        return m_view;
    }

private:
    std::vector<std::tuple<Ts&...>> m_view{};
    ComponentStorage& m_componentStorage;

    template <typename T = Entity, typename... Rest>
    std::vector<Entity> getEntities(size_t entityCount)
    {
        auto container = m_componentStorage.getContainer<T>();

        if (container->size() == entityCount)
        {
            return container->getEntities();
        }

        return getEntities<Rest...>(entityCount);
    }
};

class ViewManager final
{
public:
    ViewManager() = delete;
    ViewManager(ComponentStorage& storage) : m_componentStorage{storage} {}

    template <typename... Ts>
    std::vector<std::tuple<Ts&...>> get()
    {
        auto view = getViewInstance<Ts...>();
        return view->get();
    }

private:
    ComponentStorage& m_componentStorage;

    ViewId m_viewCounter{0};
    std::vector<std::shared_ptr<IView>> m_views{};

    template <typename... Ts>
    ComponentId getViewId()
    {
        static ViewId viewId{m_viewCounter++};
        return viewId;
    }

    template <typename... Ts>
    std::shared_ptr<View<Ts...>> getViewInstance()
    {
        auto id = getViewId<Ts...>();

        if (id >= m_views.size())
        {
            m_views.push_back(std::make_shared<View<Ts...>>(m_componentStorage));
        }

        return std::static_pointer_cast<View<Ts...>>(m_views[id]);
    }
};

} // namespace engine::ecs
