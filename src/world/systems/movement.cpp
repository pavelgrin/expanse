#include <engine/ecs.hpp>
#include <world/components/movement.hpp>
#include <world/systems/movement.hpp>

namespace world::system
{
void movementSystem(float dt)
{
    auto movementView = engine::ecs::view<
        world::component::Position, world::component::Velocity>();

    for (auto& [position, velocity] : movementView)
    {
        position.m_x += velocity.m_x * dt;
        position.m_y += velocity.m_y * dt;
    }
}
} // namespace world::system
