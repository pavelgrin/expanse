#pragma once

#include <engine/ecs/system_manager.hpp>

namespace engine::ecs
{

class Managers
{
    static inline SystemManager m_systemManager{};

public:
    friend void update(float);

    template <SystemManager::SystemType system>
    friend void registerSystem();
};

void update(float);

template <SystemManager::SystemType system>
void registerSystem()
{
    Managers::m_systemManager.registerSystem<system>();
}

} // namespace engine::ecs
