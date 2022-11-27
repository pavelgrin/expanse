#include <engine/engine.hpp>
#include <world/world.hpp>

int main()
{
    world::init();
    return engine::run();
}
