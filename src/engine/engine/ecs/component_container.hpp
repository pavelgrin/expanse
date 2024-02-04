#pragma once

#include <engine/ecs/types.hpp>

namespace engine::ecs
{
class IComponentContainer
{
public:
    virtual ~IComponentContainer() = default;

    virtual void remove(const Entity) = 0;
    virtual bool has(const Entity)    = 0;
    virtual size_t size()             = 0;
};

template <typename T>
class ComponentContainer final : public IComponentContainer
{
    std::unordered_map<Entity, T> m_components;
    T m_stubComponent{};

public:
    void add(const Entity id, T&& comp)
    {
        m_components.insert(std::make_pair(id, std::move(comp)));
    }

    T& get(const Entity id)
    {
        // [NOTE][cppcheck] False positive error for 1.90 version
        // [TODO] Install a newer version or find another solution
        // cppcheck-suppress stlIfFind
        if (const auto& container = m_components.find(id); container != m_components.end())
        {
            return container->second;
        }

        assert("Trying to get component with invalid entity id");

        // Should never reach this line, but it's necessary because of
        // "Warning: control reaches end of non-void function [-Wreturn-type]"
        return m_stubComponent;
    }

    void remove(const Entity id) override
    {
        m_components.erase(id);
    }

    bool has(const Entity id) override
    {
        return static_cast<bool>(m_components.count(id));
    }

    size_t size() override
    {
        return m_components.size();
    }

    std::vector<Entity> getEntities()
    {
        std::vector<Entity> entities{};
        entities.reserve(m_components.size());

        for (const auto& [e, _] : m_components)
        {
            entities.push_back(e);
        }

        return entities;
    }
};
} // namespace engine::ecs
