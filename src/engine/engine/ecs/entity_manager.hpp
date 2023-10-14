#pragma once

#include <engine/ecs/component_storage.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class EntityManager final
{
    ComponentStorage& m_componentStorage;

public:
    EntityManager() = delete;
    EntityManager(ComponentStorage& storage) : m_componentStorage{storage} {}

    Entity createEntity()
    {
        const auto& componentContainer = m_componentStorage.getContainer<Entity>();
        const auto entityId            = static_cast<Entity>(componentContainer->size());

        componentContainer->add(entityId, m_componentStorage.getComponentId<Entity>());

        return entityId;
    }

    void destroyEntity(Entity entityId)
    {
        m_componentStorage.removeComponentsByEntity(entityId);
    }

    template <typename T>
    bool hasComponent(Entity entityId)
    {
        const auto& componentContainer = m_componentStorage.getContainer<T>();

        return componentContainer->has(entityId);
    }

    template <typename T>
    void addComponent(Entity entityId, T&& component)
    {
        const auto componentId       = m_componentStorage.getComponentId<T>();
        const auto entityComponentId = m_componentStorage.getComponentId<Entity>();

        assert(componentId != entityComponentId && "Entity cannot be added by this method");

        const auto& componentContainer = m_componentStorage.getContainer<T>();

        if (!componentContainer->has(entityId))
        {
            componentContainer->add(entityId, std::move(component));
        }
    }

    template <typename T>
    void removeComponent(Entity entityId)
    {
        const auto componentId       = m_componentStorage.getComponentId<T>();
        const auto entityComponentId = m_componentStorage.getComponentId<Entity>();

        assert(componentId != entityComponentId && "Entity cannot be deleted by this method");

        const auto& componentContainer = m_componentStorage.getContainer<T>();

        if (componentContainer->has(entityId))
        {
            componentContainer->remove(entityId);
        }
    }

    template <typename T>
    T& getComponent(Entity entityId)
    {
        const auto& componentContainer = m_componentStorage.getContainer<T>();
        return componentContainer->get(entityId);
    }
};
} // namespace engine::ecs
