#ifndef THERMOENGINE_CAMERA2D_H
#define THERMOENGINE_CAMERA2D_H

#include <glm/glm.hpp>

namespace Thermo
{
    class Camera2D
    {
    public:
        Camera2D(float width, float height, float zoom = 5.0f);

        [[nodiscard]] inline glm::mat4 GetViewProjMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }

        void SetSize(float width, float height);

    private:
        void RecalculateViewMatrix();
        void RecalculateProjectionMatrix();

    private:
        glm::mat4 m_ViewMatrix{};
        glm::mat4 m_ProjectionMatrix{};

        glm::vec3 m_Position;
        glm::vec3 m_Rotation;

        float m_AspectRatio;
        float m_Zoom;
    };
} // Thermo

#endif //THERMOENGINE_CAMERA2D_H
