#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace Thermo
{
    class Camera
    {
    public:
        virtual ~Camera() = default;

        [[nodiscard]] virtual glm::mat4 GetViewProjectionMatrix() const = 0;
    };
}
#endif //CAMERA_H
