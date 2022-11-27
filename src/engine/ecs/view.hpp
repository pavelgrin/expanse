#pragma once

#include <tuple>
#include <vector>

namespace engine::ecs
{
template <typename... Ts>
std::vector<std::tuple<Ts&...>> view()
{
    // std::vector managedEntities;
    // std::tie(getComponentContainer<Ts>(entity)...);
    // std::vector<std::tuple<Ts&...>> list
    // return list;
}
} // namespace engine::ecs
