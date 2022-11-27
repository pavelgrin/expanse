#include <engine/ecs.hpp>
#include <engine/ecs/system_manager.hpp>

#include <world/systems/movement.hpp>

namespace engine::ecs
{
SystemManager systemManager{};

void update()
{
    systemManager.update();
}

void registerSystem(SystemFunction f)
{
    systemManager.registerSystem();
}

} // namespace engine::ecs
