#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

namespace engine::ecs
{
using SystemType  = void (*)(float);
using ComponentId = uint32_t;
using Entity      = uint32_t;
} // namespace engine::ecs
