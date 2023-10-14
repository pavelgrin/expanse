#include <world/components/movement.hpp>
#include <world/systems/movement.hpp>
#include <world/world.hpp>

#include <engine/ecs.hpp>

namespace world
{
void init()
{
    const auto entity = engine::ecs::createEntity();

    engine::ecs::addComponent<world::component::Position>(entity, {0.f, 0.f});
    engine::ecs::addComponent<world::component::Velocity>(entity, {0.5f, 0.5f});

    engine::ecs::registerSystem<world::system::movementSystem>();
    engine::ecs::registerSystem<world::system::printSystem>();
}
} // namespace world
