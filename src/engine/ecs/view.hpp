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
    std::unordered_set<Entity> m_matchedEntities{};

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
                m_matchedEntities.insert(e);
            }
        }

        updateView();
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
        bool isSuitable = (m_componentStorage.getContainer<Ts>()->has(e) && ...);
        bool hasEntity  = static_cast<bool>(m_matchedEntities.count(e));

        if (isSuitable && !hasEntity)
        {
            m_matchedEntities.insert(e);
            updateView();
        }
        else if (!isSuitable && hasEntity)
        {
            m_matchedEntities.erase(e);
            updateView();
        }
    }

    void updateView()
    {
        m_view.clear();
        for (const auto e : m_matchedEntities)
        {
            m_view.push_back(std::tie(m_componentStorage.getContainer<Ts>()->get(e)...));
        }
    }
};

class ViewManager final
{
    using ViewStorageItem = std::shared_ptr<IView>;
    using ViewStorage     = std::vector<ViewStorageItem>;

    ComponentStorage& m_componentStorage;

    ViewId m_viewCounter{0};

    ViewStorage m_viewStorage{};
    std::unordered_map<ComponentId, ViewStorage> m_viewMap{};

public:
    ViewManager() = delete;
    ViewManager(ComponentStorage& storage) : m_componentStorage{storage} {}

    template <typename... Ts>
    std::vector<std::tuple<Ts&...>> getView()
    {
        const auto& view = getViewInstance<Ts...>();
        return view->get();
    }

    void updateViews(Entity e)
    {
        for (const auto& view : m_viewStorage)
        {
            view->update(e);
        }
    }

    template <typename T>
    void updateViews(Entity e)
    {
        const auto componentId = m_componentStorage.getComponentId<T>();

        if (const auto& pair = m_viewMap.find(componentId); pair != m_viewMap.end())
        {
            for (const auto& view : pair->second)
            {
                view->update(e);
            }
        }
    }

private:
    template <typename... Ts>
    ComponentId getViewId()
    {
        static ViewId viewId{m_viewCounter++};
        return viewId;
    }

    template <typename... Ts>
    std::shared_ptr<View<Ts...>> getViewInstance()
    {
        const auto id = getViewId<Ts...>();

        if (id >= m_viewStorage.size())
        {
            const auto view{std::make_shared<View<Ts...>>(m_componentStorage)};
            m_viewStorage.push_back(view);

            (updateViewMap<Ts>(view), ...);
        }

        return std::static_pointer_cast<View<Ts...>>(m_viewStorage[id]);
    }

    template <typename T>
    void updateViewMap(const ViewStorageItem& view)
    {
        const auto componentId = m_componentStorage.getComponentId<T>();

        if (const auto& pair = m_viewMap.find(componentId); pair != m_viewMap.end())
        {
            pair->second.push_back(view);
        }
        else
        {
            ViewStorage storage{view};
            m_viewMap.insert(std::make_pair(componentId, storage));
        }
    }
};

} // namespace engine::ecs
