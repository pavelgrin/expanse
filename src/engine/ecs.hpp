#pragma once

#include <engine/ecs/component_storage.hpp>
#include <engine/ecs/entity_manager.hpp>
#include <engine/ecs/system_manager.hpp>
#include <engine/ecs/types.hpp>
#include <engine/ecs/view.hpp>

#include <tuple>
#include <vector>

namespace engine::ecs
{

class ECS final
{
private:
    ECS() = default;

    static inline ComponentStorage m_componentStorage{};

    static inline EntityManager m_entityManager{m_componentStorage};
    static inline View m_view{m_componentStorage};

    static inline SystemManager m_systemManager{};

    friend void update(float);

    friend Entity createEntity();
    friend void destroyEntity(Entity);

    template <typename T>
    friend void addComponent(Entity, T&&);

    template <typename T>
    friend void removeComponent(Entity);

    template <typename T>
    friend T& getComponent(Entity);

    template <SystemType system>
    friend void registerSystem();

    template <typename T, typename... Ts>
    friend std::vector<std::tuple<T&, Ts&...>> view();
};

inline void update(float dt)
{
    ECS::m_systemManager.update(dt);
}

inline Entity createEntity()
{
    return ECS::m_entityManager.createEntity();
}

inline void destroyEntity(Entity entity)
{
    ECS::m_entityManager.destroyEntity(entity);
}

template <typename T>
void addComponent(Entity entity, T&& comp)
{
    ECS::m_entityManager.addComponent<T>(entity, std::move(comp));
}

template <typename T>
void removeComponent(Entity entity)
{
    ECS::m_entityManager.removeComponent<T>(entity);
}

template <typename T>
T& getComponent(Entity entity)
{
    return ECS::m_entityManager.getComponent<T>(entity);
}

template <SystemType system>
void registerSystem()
{
    ECS::m_systemManager.registerSystem<system>();
}

template <typename T, typename... Ts>
std::vector<std::tuple<T&, Ts&...>> view()
{
    return ECS::m_view.get<T, Ts...>();
}

} // namespace engine::ecs
