#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <entt.h>

namespace Thermo
{
    typedef uint32_t EntityId;

    struct ComponentWrapper
    {
        size_t typeId;
        void *data = nullptr;
    };


    class EntityManager
    {
    public:
        EntityId CreateEntity()
        {
            const auto entity = static_cast<EntityId>(m_Registry.create());
            m_Entities.push_back(entity);
            return entity;
        }

        void DestroyEntity(const EntityId entityId)
        {
            m_Registry.destroy(static_cast<entt::entity>(entityId));
            m_Entities.erase(std::ranges::find(m_Entities, entityId));
        }

        template<typename Component, typename... Args>
        Component &AddComponent(const EntityId entityId, Args &&... args)
        {
            m_Registry.emplace<Component, Args...>(static_cast<entt::entity>(entityId), std::forward<Args>(args)...);

            Component &component = GetComponent<Component>(entityId);

            auto wrapper = ComponentWrapper();

            wrapper.typeId = typeid(Component).hash_code();
            wrapper.data = &component;

            const auto componentTypeId = typeid(Component).hash_code();

            m_EntityComponents[entityId][componentTypeId] = wrapper;

            return component;
        }

        template<typename Component>
        Component &GetComponent(const EntityId entityId)
        {
            return m_Registry.get<Component>(static_cast<entt::entity>(entityId));
        }

        template<typename Component>
        void RemoveComponent(const EntityId entityId)
        {
            m_Registry.remove<Component>(static_cast<entt::entity>(entityId));
            m_EntityComponents[entityId].erase(typeid(Component).hash_code());
        }

        entt::registry &GetRegistry()
        {
            return m_Registry;
        }

        const std::vector<EntityId> &GetEntities()
        {
            return m_Entities;
        }

        const std::map<unsigned long, ComponentWrapper> &
        GetAllComponents(const EntityId entity)
        {
            return m_EntityComponents[entity];
        }

    private:
        entt::registry m_Registry;
        std::vector<EntityId> m_Entities;
        std::unordered_map<EntityId, std::map<size_t, ComponentWrapper> > m_EntityComponents;
    };
} // Thermo

#endif //ENTITYMANAGER_H
