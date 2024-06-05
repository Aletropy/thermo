#ifndef THERMOENGINE_SYSTEMMANAGER_H
#define THERMOENGINE_SYSTEMMANAGER_H

#include <vector>
#include "System.h"

namespace Thermo
{
    using SystemPtr = std::shared_ptr<System>;

    class SystemManager
    {
    public:

        template<typename T, typename ... Args>
        void PushSystem(Args&& ... args)
        {
            m_Systems.push_back(std::make_shared<T>(std::forward<Args>(args)...));
        }

        void UpdateSystems(float deltaTime);
        void InitializeSystems();

    private:
        std::vector<SystemPtr> m_Systems;
    };

} // Thermo

#endif //THERMOENGINE_SYSTEMMANAGER_H
