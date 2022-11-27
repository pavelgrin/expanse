#pragma once

namespace engine::ecs
{
class SystemManager
{
public:
    void update();
    void registerSystem();
};
} // namespace engine::ecs
