#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <entt.h>

namespace Thermo
{
    typedef uint32_t EntityId;

    class EntityManager
    {
    public:
        EntityId CreateEntity()
        {
            return static_cast<EntityId>(m_Registry.create());
        }

        void DestroyEntity(const EntityId entityId)
        {
            m_Registry.destroy(static_cast<entt::entity>(entityId));
        }

        template<typename Component, typename ... Args>
        void AddComponent(const EntityId entityId, Args&& ... args)
        {
            m_Registry.emplace<Component, Args...>(static_cast<entt::entity>(entityId), std::forward<Args>(args)...);
        }

        template<typename Component>
        Component& GetComponent(const EntityId entityId)
        {
            return m_Registry.get<Component>(static_cast<entt::entity>(entityId));
        }

        template<typename Component>
        void RemoveComponent(const EntityId entityId)
        {
            m_Registry.remove<Component>(static_cast<entt::entity>(entityId));
        }

        entt::registry& GetRegistry()
        {
            return m_Registry;
        }

    private:
        entt::registry m_Registry;
    };

} // Thermo

#endif //ENTITYMANAGER_H
