#include "LayerStack.h"

namespace Thermo
{
    void LayerStack::UpdateLayers(const float deltaTime)
    {
        for (const auto& m_layer : m_Layers)
        {
            m_layer->OnUpdate(deltaTime);
        }
    }

} // Thermo