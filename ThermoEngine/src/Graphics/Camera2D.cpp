#include "ThermoPch.h"
#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Thermo
{
    Camera2D::Camera2D(const float width, const float height, const float zoom)
        : m_AspectRatio(width / height)
        , m_Zoom(zoom)
        , m_Position(0.0f, 0.0f, 0.0f)
        , m_Rotation(0.0f, 0.0f, 0.0f)
    {
        float aspectRatio = width / height;

        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::ortho(-zoom * aspectRatio, zoom * aspectRatio, -zoom, zoom);
    }

    void Camera2D::SetSize(const float width, const float height)
    {
        m_AspectRatio = width / height;
        RecalculateProjectionMatrix();
    }

    void Camera2D::RecalculateViewMatrix()
    {
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), -m_Position);
    }

    void Camera2D::RecalculateProjectionMatrix()
    {
        const float aspectRatio = m_AspectRatio;
        const float zoom = m_Zoom;
        m_ProjectionMatrix = glm::ortho(-zoom * aspectRatio, zoom * aspectRatio, -zoom, zoom);
    }
} // Thermo