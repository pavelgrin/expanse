#include <cassert>

namespace engine::ecs
{
class ComponentManager
{
public:
    template <typename T>
    void registerComponent()
    {
        static bool isRegistered{false};
        assert(!isRegistered && "Registering component type more than once");
        isRegistered = true;

        // The first call is needed to init component id of type T
        getComponentId<T>();
        m_idCounter += 1;
    }

    template <typename T>
    int getComponentId()
    {
        static int componentId{m_idCounter};
        return componentId;
    }

private:
    int m_idCounter{0};
};
} // namespace engine::ecs
