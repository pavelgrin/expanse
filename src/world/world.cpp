#include <world/components/movement.hpp>
#include <world/systems/movement.hpp>
#include <world/world.hpp>

#include <engine/ecs.hpp>

namespace world
{
void init()
{
    auto entity = engine::ecs::createEntity();

    engine::ecs::addComponent<world::component::Position>(entity, {0, 0});
    engine::ecs::addComponent<world::component::Velocity>(entity, {1, 0});

    engine::ecs::registerSystem<world::system::movementSystem>();
    engine::ecs::registerSystem<world::system::printSystem>();
}
} // namespace world
