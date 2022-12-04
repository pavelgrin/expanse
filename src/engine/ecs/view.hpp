#pragma once

#include <tuple>
#include <vector>

#include <iostream>

namespace engine::ecs
{
class View
{
public:
    template <typename... Ts>
    std::vector<std::tuple<Ts&...>> get()
    {
        std::vector<std::tuple<Ts&...>> view{};
        return view;
    }
};
} // namespace engine::ecs
