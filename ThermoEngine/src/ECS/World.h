#ifndef WORLD_H
#define WORLD_H

#include "SystemManager.h"

namespace Thermo
{
    class World 
    {
    public:
        explicit World(const std::string& debugName);

        template<typename T, typename ... Args>
        void PushSystem(Args&& ... args)
        {
            m_SystemManager.PushSystem<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        void PushEntitySystem()
        {
            m_SystemManager.PushSystem<T>(m_EntityManager);
        }

        void Update(float deltaTime);

        const std::string& GetDebugName() const { return m_DebugName; }

    private:
        const std::string m_DebugName;
        SystemManager m_SystemManager;
        Ref<EntityManager> m_EntityManager;
    };

} // ThermoEngine

#endif //WORLD_H
