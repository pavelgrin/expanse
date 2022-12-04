#pragma once

#include <engine/ecs/component_manager.hpp>
#include <engine/ecs/entity_manager.hpp>
#include <engine/ecs/system_manager.hpp>
#include <engine/ecs/view.hpp>

#include <tuple>
#include <vector>

namespace engine::ecs
{

class ECS
{
    ECS() = default;

    static inline ComponentManager m_componentManager{};
    static inline EntityManager m_entityManager{};
    static inline SystemManager m_systemManager{};
    static inline View m_view{};

public:
    friend void update(float);

    template <typename T>
    friend void registerComponent();

    template <SystemManager::SystemType system>
    friend void registerSystem();

    template <typename... Ts>
    friend std::vector<std::tuple<Ts&...>> view();
};

inline void update(float dt)
{
    ECS::m_systemManager.update(dt);
}

template <typename T>
void registerComponent()
{
    ECS::m_componentManager.registerComponent<T>();
}

template <SystemManager::SystemType system>
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
