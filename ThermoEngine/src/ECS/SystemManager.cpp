#include "ThermoPch.h"
#include "SystemManager.h"

namespace Thermo
{
    void SystemManager::UpdateSystems(const float deltaTime)
    {
        for(const auto& system : m_Systems)
        {
            system->Update(deltaTime);
        }
    }

    void SystemManager::InitializeSystems()
    {
        for(const auto& system : m_Systems)
        {
            system->Initialize();
        }
    }
} // Thermo