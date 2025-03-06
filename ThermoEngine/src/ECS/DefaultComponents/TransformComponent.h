#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "glm/vec3.hpp"

namespace Thermo
{
    class TransformComponent
    {
    public:
        glm::vec3 Position = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);
        glm::vec3 Rotation = glm::vec3(0.0f);
    };
}

#endif //TRANSFORM_H
