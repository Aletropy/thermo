#include "ThermoPch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Thermo
{
    OrthographicCamera::OrthographicCamera(const float width, const float height, const float zoom)
        : m_AspectRatio(width / height)
          , m_Zoom(zoom)
          , m_Position(0.0f, 0.0f, 0.0f)
          , m_Rotation(0.0f, 0.0f, 0.0f)
    {
        float aspectRatio = width / height;

        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::ortho(-zoom * aspectRatio, zoom * aspectRatio, -zoom, zoom);
    }

    void OrthographicCamera::SetSize(const float width, const float height)
    {
        m_AspectRatio = width / height;
        RecalculateProjectionMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), -m_Position);
    }

    void OrthographicCamera::RecalculateProjectionMatrix()
    {
        const float aspectRatio = m_AspectRatio;
        const float zoom = m_Zoom;
        m_ProjectionMatrix = glm::ortho(-zoom * aspectRatio, zoom * aspectRatio, -zoom, zoom);
    }
} // Thermo
