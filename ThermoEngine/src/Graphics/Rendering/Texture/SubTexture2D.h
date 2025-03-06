#ifndef SUBTEXTURE2D_H
#define SUBTEXTURE2D_H

#include "Texture2D.h"
#include "Core/Base.h"
#include "glm/vec2.hpp"

namespace Thermo
{
    struct SubTexture2D
    {
        Ref<Texture2D> Texture;
        glm::vec2 Offset;
        glm::vec2 Size;
    };
}

#endif //SUBTEXTURE2D_H
