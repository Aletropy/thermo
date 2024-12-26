#ifndef THERMOENGINE_LAYERSTACK_H
#define THERMOENGINE_LAYERSTACK_H

#include <vector>
#include "Layer.h"

namespace Thermo
{
    using LayerPtr = std::shared_ptr<Layer>;

    class LayerStack
    {
    public:
        template<typename T, typename ... Args>
        void PushLayer(Args&& ... args)
        {
            auto sharedPtr = std::make_shared<T>(std::forward<Args>(args)...);
            m_Layers.insert(m_Layers.begin() + m_OverlayIndex, sharedPtr);
            m_OverlayIndex++;
            sharedPtr->OnAttach();
        }

        template<typename T, typename ... Args>
        void PushOverlay(Args&& ... args)
        {
            auto sharedPtr = std::make_shared<T>(std::forward<Args>(args)...);
            m_Layers.push_back(sharedPtr);
            m_OverlayCount++;
            sharedPtr->OnAttach();
        }


        void UpdateLayers(float deltaTime);
        void OnEvent(Event& event);

        auto begin() { return m_Layers.begin(); }
        auto end() { return m_Layers.end(); }
        auto rbegin() { return m_Layers.rbegin(); }
        auto rend() { return m_Layers.rend(); }

    private:
        std::vector<LayerPtr> m_Layers;
        size_t m_OverlayIndex = 0;
        size_t m_OverlayCount = 0;
    };

} // Thermo

#endif //THERMOENGINE_LAYERSTACK_H
