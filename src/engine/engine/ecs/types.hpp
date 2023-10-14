#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace engine::ecs
{
using SystemType  = void (*)(float);
using ComponentId = uint32_t;
using ViewId      = uint32_t;
using Entity      = uint32_t;
} // namespace engine::ecs
