#include "ThermoPch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Thermo
{
    PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float nearClip, float farClip)
        : m_FOV(fov), m_AspectRatio(width / height), m_NearClip(nearClip), m_FarClip(farClip)
    {
        RecalculateProjectionMatrix();
        RecalculateViewMatrix();
    }

    void PerspectiveCamera::SetSize(float width, float height)
    {
        m_AspectRatio = width / height;
        RecalculateProjectionMatrix();
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), -m_Position);
        m_ViewMatrix = transform;
    }

    void PerspectiveCamera::RecalculateProjectionMatrix()
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }
} // namespace Thermo
