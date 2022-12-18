#pragma once

#include <engine/ecs/component_storage.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class EntityManager final
{
public:
    EntityManager() = delete;
    EntityManager(ComponentStorage& storage) : m_componentStorage{storage} {}

    Entity createEntity()
    {
        auto componentId        = m_componentStorage.getComponentId<Entity>();
        auto componentContainer = m_componentStorage.getContainer<Entity>(componentId);
        auto entityId           = static_cast<Entity>(componentContainer->size());

        componentContainer->add(entityId, std::move(componentId));

        return entityId;
    }

    void destroyEntity(Entity entityId)
    {
        m_componentStorage.removeComponentsByEntity(entityId);
    }

    template <typename T>
    bool hasComponent(Entity entityId)
    {
        auto componentId        = m_componentStorage.getComponentId<T>();
        auto componentContainer = m_componentStorage.getContainer<T>(componentId);

        return componentContainer->has(entityId);
    }

    template <typename T>
    void addComponent(Entity entityId, T&& component)
    {
        auto componentId       = m_componentStorage.getComponentId<T>();
        auto entityComponentId = m_componentStorage.getComponentId<Entity>();

        assert(componentId != entityComponentId && "Entity cannot be added by this method");

        auto componentContainer = m_componentStorage.getContainer<T>(componentId);

        if (!componentContainer->has(entityId))
        {
            componentContainer->add(entityId, std::move(component));
        }
    }

    template <typename T>
    void removeComponent(Entity entityId)
    {
        auto componentId       = m_componentStorage.getComponentId<T>();
        auto entityComponentId = m_componentStorage.getComponentId<Entity>();

        assert(componentId != entityComponentId && "Entity cannot be deleted by this method");

        auto componentContainer = m_componentStorage.getContainer<T>(componentId);

        if (componentContainer->has(entityId))
        {
            componentContainer->remove(entityId);
        }
    }

    template <typename T>
    T& getComponent(Entity entityId)
    {
        auto componentId        = m_componentStorage.getComponentId<T>();
        auto componentContainer = m_componentStorage.getContainer<T>(componentId);
        return componentContainer->get(entityId);
    }

private:
    ComponentStorage& m_componentStorage;
};
} // namespace engine::ecs
