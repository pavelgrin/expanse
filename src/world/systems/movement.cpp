#include <engine/ecs.hpp>
#include <world/components/movement.hpp>
#include <world/systems/movement.hpp>

#include <iostream>

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

void printSystem(float dt)
{
    auto movementView = engine::ecs::view<
        world::component::Position, world::component::Velocity>();

    for (auto& [position, velocity] : movementView)
    {
        std::cout << "Position: X: " << position.m_x << " / Y: " << position.m_y << std::endl;
    }
}
} // namespace world::system
