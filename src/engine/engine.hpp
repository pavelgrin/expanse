namespace engine
{
class Engine
{
private:
    enum class State
    {
        Running,
        Stopped,
    };

    State m_state{};

public:
    Engine(/* args */);
    ~Engine();

    int run();
};

} // namespace engine
