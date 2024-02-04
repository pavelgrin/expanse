#pragma once

#include <engine/ecs/component_container.hpp>
#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class ComponentStorage final
{
    ComponentId m_componentCounter{0};
    std::vector<std::shared_ptr<IComponentContainer>> m_componentContainers{};

public:
    ComponentStorage()                        = default;
    ComponentStorage(ComponentStorage& other) = delete;
    void operator=(const ComponentStorage&) = delete;

    void removeComponentsByEntity(Entity entityId)
    {
        for (const auto& componentContainer : m_componentContainers)
        {
            if (componentContainer->has(entityId))
            {
                componentContainer->remove(entityId);
            }
        }
    }

    template <typename T>
    std::shared_ptr<ComponentContainer<T>> getContainer()
    {
        const auto id = getComponentId<T>();

        if (id >= m_componentContainers.size())
        {
            m_componentContainers.push_back(std::make_shared<ComponentContainer<T>>());
        }

        return std::static_pointer_cast<ComponentContainer<T>>(m_componentContainers[id]);
    }

    template <typename T>
    ComponentId getComponentId()
    {
        static ComponentId componentId{m_componentCounter++};
        return componentId;
    }
};
} // namespace engine::ecs
