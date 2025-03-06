#ifndef QUADRENDERER_H
#define QUADRENDERER_H
#include "glm/vec4.hpp"
#include "Graphics/Colors.h"

namespace Thermo
{
    class QuadRendererComponent
    {
    public:
        glm::vec4 Color = Colors::WHITE;
    };
}

#endif //QUADRENDERER_H
