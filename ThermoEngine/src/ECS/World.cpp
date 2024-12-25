#include "ThermoPch.h"
#include "World.h"

namespace Thermo
{
    World::World(const std::string &debugName)
        : m_DebugName(debugName)
    {
        m_EntityManager = CreateRef<EntityManager>();
    }

    void World::Update(const float deltaTime)
    {
        m_SystemManager.UpdateSystems(deltaTime);
    }
} // ThermoEngine