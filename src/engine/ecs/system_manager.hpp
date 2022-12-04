#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace engine::ecs
{
class SystemManager
{
public:
    using SystemType = void (*)(float);

    void update(float);

    template <SystemType system>
    void registerSystem()
    {
        std::cout << "register System" << std::endl;

        bool wasRegistered = std::find(m_systems.begin(), m_systems.end(), system) != m_systems.end();
        assert(!wasRegistered && "Registering system more than once.");

        m_systems.emplace_back(system);
    }

private:
    std::vector<SystemType> m_systems{};
};
} // namespace engine::ecs
