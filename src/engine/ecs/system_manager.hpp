#pragma once

#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class SystemManager final
{
    std::vector<SystemType> m_systems{};

public:
    void update(float dt)
    {
        for (const auto& system : m_systems)
        {
            system(dt);
        }
    }

    template <SystemType system>
    void registerSystem()
    {
        static bool isRegistered{false};
        assert(!isRegistered && "Registering system more than once");
        isRegistered = true;

        m_systems.push_back(system);
    }
};
} // namespace engine::ecs
