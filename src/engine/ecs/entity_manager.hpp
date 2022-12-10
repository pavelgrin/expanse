#pragma once

#include <engine/ecs/component_manager.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class EntityManager final
{
public:
    Entity createEntity()
    {
        auto componentId  = getComponentId<Entity>();
        auto componentMap = getComponentMap<Entity>(componentId);
        auto entityId     = static_cast<Entity>(componentMap->size());

        componentMap->insert(entityId, entityId);

        return entityId;
    }

    void destroyEntity(Entity entityId)
    {
        for (auto componentMap : m_componentMaps)
        {
            componentMap->erase(entityId);
        }
    }

    template <typename T>
    void addComponent(Entity entityId, T component)
    {
        auto componentId       = getComponentId<T>();
        auto entityComponentId = getComponentId<Entity>();

        assert(componentId != entityComponentId && "Entity cannot be added by this method");

        auto componentMap = getComponentMap<T>(componentId);

        if (!componentMap->has(entityId))
        {
            componentMap->insert(entityId, component);
        }
    }

    template <typename T>
    void removeComponent(Entity entityId)
    {
        auto componentId       = getComponentId<T>();
        auto entityComponentId = getComponentId<Entity>();

        assert(componentId != entityComponentId && "Entity cannot be deleted by this method");

        auto componentMap = getComponentMap<T>(componentId);

        if (componentMap->has(entityId))
        {
            componentMap->erase(entityId);
        }
    }

    template <typename T>
    T& getComponent(Entity entityId)
    {
        auto componentId  = getComponentId<T>();
        auto componentMap = getComponentMap<T>(componentId);
        return componentMap->get(entityId);
    }

private:
    ComponentId m_componentCounter{0};
    std::vector<std::shared_ptr<IComponentMap>> m_componentMaps{};

    template <typename T>
    std::shared_ptr<ComponentMap<T>> getComponentMap(ComponentId id)
    {
        if (id >= m_componentMaps.size())
        {
            m_componentMaps.emplace_back(std::make_shared<ComponentMap<T>>());
        }

        return std::static_pointer_cast<ComponentMap<T>>(m_componentMaps[id]);
    }

    template <typename T>
    ComponentId getComponentId()
    {
        static bool isFirstCall{true};
        static ComponentId componentId{0};

        if (isFirstCall)
        {
            componentId = m_componentCounter;

            m_componentCounter += 1;
            isFirstCall = false;
        }

        return componentId;
    }
};
} // namespace engine::ecs
