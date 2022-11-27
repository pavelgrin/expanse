#pragma once

using SystemFunction = void (*)(float);

namespace engine::ecs
{

void update();
void registerSystem(SystemFunction f);

} // namespace engine::ecs
