#include <engine/engine.hpp>
#include <world/world.hpp>

int main()
{
    world::init();
    engine::run();

    return 0;
}
