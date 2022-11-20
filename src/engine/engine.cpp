#include "./engine.hpp"
#include <iostream>

using namespace engine;

Engine::Engine(/* args */)
{
}

Engine::~Engine()
{
}

int Engine::run()
{
    m_state = Engine::State::Running;
    while (m_state == Engine::State::Running)
    {
        /* code */

        m_state = Engine::State::Stopped;
    }

    return 0;
}
