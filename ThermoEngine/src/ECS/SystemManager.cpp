#include "ThermoPch.h"
#include "SystemManager.h"

namespace Thermo
{
    void SystemManager::UpdateSystems(float deltaTime)
    {
        for(auto& system : m_Systems)
        {
            system->Update(deltaTime);
        }
    }

    void SystemManager::InitializeSystems()
    {
        for(auto& system : m_Systems)
        {
            system->Initialize();
        }
    }
} // Thermo