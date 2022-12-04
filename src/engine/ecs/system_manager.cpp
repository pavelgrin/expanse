#include <engine/ecs/system_manager.hpp>

namespace engine::ecs
{
void SystemManager::update(float dt)
{
    std::cout << "update Systems" << std::endl;

    for (auto& system : m_systems)
    {
        system(dt);
    }
}
} // namespace engine::ecs
