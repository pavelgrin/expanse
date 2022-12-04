#include <world/components/movement.hpp>
#include <world/systems/movement.hpp>
#include <world/world.hpp>

#include <engine/ecs.hpp>

namespace world
{
void init()
{
    engine::ecs::registerComponent<world::component::Position>();
    engine::ecs::registerComponent<world::component::Velocity>();

    // auto entity = engine::ecs::createEntity();
    // entity.add<movement::Position>({0, 0});
    // entity.add<movement::Velocity>({1, 0});

    engine::ecs::registerSystem<world::system::movementSystem>();
}
} // namespace world
