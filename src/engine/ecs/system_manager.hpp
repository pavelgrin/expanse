#pragma once

#include <cassert>
#include <vector>

namespace engine::ecs
{
class SystemManager
{
public:
    using SystemType = void (*)(float);

    void update(float dt)
    {
        for (auto& system : m_systems)
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

        m_systems.emplace_back(system);
    }

private:
    std::vector<SystemType> m_systems{};
};
} // namespace engine::ecs
