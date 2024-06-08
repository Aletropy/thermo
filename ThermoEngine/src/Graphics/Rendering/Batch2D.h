#ifndef THERMOENGINE_BATCH2D_H
#define THERMOENGINE_BATCH2D_H

#include <glm/glm.hpp>
#include "Graphics/Camera2D.h"

namespace Thermo
{

    class Batch2D
    {
    public:
        static void Initialize();

        static void SetCamera(const Ref<Camera2D>& camera);

        static void BeginBatch();
        static void PushQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color = glm::vec4(0.0f));
        static void PushCircle(const glm::vec2& position, float radius, const glm::vec2& rotation, const glm::vec4& color = glm::vec4(0.0f));
        static void EndBatch();

        static void Shutdown();
    private:
        static void NextBatch();
        static void Flush();
    };

} // Thermo

#endif //THERMOENGINE_BATCH2D_H
