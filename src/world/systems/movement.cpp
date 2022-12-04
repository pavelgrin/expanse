// #include <engine/ecs/view.hpp>
#include <world/components/movement.hpp>
#include <world/systems/movement.hpp>

#include <iostream>

namespace world::system
{
void movementSystem(float dt = 0.f)
{
    std::cout << "call movementSystem" << std::endl;

    // auto movementView = engine::ecs::view<
    //     world::component::Position, world::component::Velocity>();

    // for (auto& [position, velocity] : movementView)
    // {
    //     position.m_x += velocity.m_x * dt;
    //     position.m_y += velocity.m_y * dt;
    // }
}

void testSystem(float dt)
{
    std::cout << "call testSystem" << std::endl;
}
} // namespace world::system
