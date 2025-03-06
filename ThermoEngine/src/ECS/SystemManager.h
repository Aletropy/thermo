#ifndef THERMOENGINE_SYSTEMMANAGER_H
#define THERMOENGINE_SYSTEMMANAGER_H

#include <vector>
#include "ISystem.h"

namespace Thermo
{
    using SystemPtr = std::unique_ptr<ISystem>;

    class SystemManager
    {
    public:
        template<typename T, typename... Args>
        void PushSystem(Args &&... args)
        {
            static_assert(std::is_base_of_v<ISystem, T>, "T must be derived from ISystem");
            m_Systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        }


        void UpdateSystems(float deltaTime);

        void InitializeSystems();

    private:
        std::vector<SystemPtr> m_Systems;
    };
} // Thermo

#endif //THERMOENGINE_SYSTEMMANAGER_H
