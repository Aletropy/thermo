#ifndef THERMOENGINE_SYSTEM_H
#define THERMOENGINE_SYSTEM_H
#include "EntityManager.h"
#include "Core/Base.h"

namespace Thermo
{
    class EntitySystem
    {
    public:
        explicit EntitySystem(const Ref<EntityManager>& entityManager) : m_EntityManager(entityManager) {}
        virtual ~EntitySystem() = default;

        virtual void Initialize() = 0;

        virtual void Update(float deltaTime) {};

    protected:
        Ref<EntityManager> m_EntityManager;
    };
} // Thermo

#endif //THERMOENGINE_SYSTEM_H
