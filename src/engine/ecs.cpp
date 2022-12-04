#include <engine/ecs.hpp>

namespace engine::ecs
{
void update(float dt)
{
    Managers::m_systemManager.update(dt);
}
} // namespace engine::ecs
