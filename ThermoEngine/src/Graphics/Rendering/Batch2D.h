#ifndef THERMOENGINE_BATCH2D_H
#define THERMOENGINE_BATCH2D_H

#include <glm/glm.hpp>

namespace Thermo
{

    class Batch2D
    {
    public:
        static void Initialize();

        static void BeginBatch();
        static void PushQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color = glm::vec4(0.0f));
        static void EndBatch();

        static void Shutdown();
    private:
        static void NextBatch();
        static void Flush();
    };

} // Thermo

#endif //THERMOENGINE_BATCH2D_H
