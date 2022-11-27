#pragma once

namespace world::component
{
struct Position final
{
    float m_x{0.f};
    float m_y{0.f};
};

struct Velocity final
{
    float m_x{0.f};
    float m_y{0.f};
};
} // namespace world::component
