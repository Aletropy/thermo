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
            m_Systems.insert(m_Systems.begin() + m_OverlayIndex, std::make_shared<T>(std::forward<Args>(args)...));
            m_OverlayIndex++;
        }

        template<typename T, typename ... Args>
        void PushOverlay(Args&& ... args)
        {
            m_Systems.push_back(std::make_shared<T>(std::forward<Args>(args)...));
            m_OverlayCount++;
        }


        void UpdateSystems(float deltaTime);
        void InitializeSystems();

        // Iteradores bidirecionais
        auto begin() { return m_Systems.begin(); }
        auto end() { return m_Systems.end(); }
        auto rbegin() { return m_Systems.rbegin(); }
        auto rend() { return m_Systems.rend(); }

    private:
        std::vector<SystemPtr> m_Systems;
        size_t m_OverlayIndex = 0;
        size_t m_OverlayCount = 0;
    };

} // Thermo

#endif //THERMOENGINE_SYSTEMMANAGER_H
