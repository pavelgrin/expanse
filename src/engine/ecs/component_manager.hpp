#pragma once

#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class IComponentMap
{
public:
    virtual size_t size()               = 0;
    virtual bool has(const Entity id)   = 0;
    virtual void erase(const Entity id) = 0;
};

template <typename T>
class ComponentMap final : public IComponentMap
{
public:
    void insert(const Entity id, T comp)
    {
        m_components.insert({id, comp});
    }

    T& get(const Entity id)
    {
        if (auto comp = m_components.find(id); comp != m_components.end())
        {
            return comp->second;
        }

        assert("Trying to get component with invalid entity id");
    }

    size_t size() override
    {
        return m_components.size();
    }

    bool has(const Entity id) override
    {
        return static_cast<bool>(m_components.count(id));
    }

    void erase(const Entity id) override
    {
        m_components.erase(id);
    }

private:
    std::unordered_map<Entity, T> m_components;
};
} // namespace engine::ecs
