#include <chrono>
#include <engine/ecs.hpp>
#include <engine/engine.hpp>

namespace engine
{
int run()
{
    using Clock  = std::chrono::steady_clock;
    using Second = std::chrono::duration<float>;

    auto tickStartTime{Clock::now()};
    auto currentTime{Clock::now()};
    Second deltaTime{};

    // Warm up engine, call all views to init caching
    engine::ecs::update(deltaTime.count());

    bool isRunning = true;

    while (isRunning)
    {
        currentTime   = Clock::now();
        deltaTime     = currentTime - tickStartTime;
        tickStartTime = currentTime;

        engine::ecs::update(deltaTime.count());

        isRunning = false;
    }

    return 0;
}
} // namespace engine
