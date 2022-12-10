#pragma once

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
    ECS() = default;

    static inline EntityManager m_entityManager{};
    static inline SystemManager m_systemManager{};
    static inline View m_view{};

public:
    friend void update(float);

    friend Entity createEntity();
    friend void destroyEntity(Entity);

    template <typename T>
    friend void addComponent(Entity, T);

    template <typename T>
    friend void removeComponent(Entity);

    template <typename T>
    friend T& getComponent(Entity);

    template <SystemType system>
    friend void registerSystem();

    template <typename... Ts>
    friend std::vector<std::tuple<Ts&...>> view();
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
void addComponent(Entity entity, T comp)
{
    ECS::m_entityManager.addComponent<T>(entity, comp);
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

template <typename... Ts>
std::vector<std::tuple<Ts&...>> view()
{
    return ECS::m_view.get<Ts...>();
}

} // namespace engine::ecs
