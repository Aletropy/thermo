#ifndef THERMOENGINE_RENDERER_H
#define THERMOENGINE_RENDERER_H

#include <glm/glm.hpp>
#include "Graphics/Rendering/Buffer/VertexArray.h"

namespace Thermo
{

    class Renderer
    {
    public:
        STATIC_CONSTRUCTORS(Renderer)

        static void Initialize();

        static void SetClearColor(const glm::vec4& color);
        static void Clear();
        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

        static void Terminate();
    };

} // Thermo

#endif //THERMOENGINE_RENDERER_H
