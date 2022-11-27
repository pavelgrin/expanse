#include <engine/ecs/system_manager.hpp>
#include <iostream>

namespace engine::ecs
{
void SystemManager::update()
{
    std::cout << "update Systems" << std::endl;
}

void SystemManager::registerSystem()
{
    std::cout << "register System" << std::endl;
}
} // namespace engine::ecs
