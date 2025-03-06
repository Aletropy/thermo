#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include <glm/glm.hpp>

#include "Camera.h"

namespace Thermo
{
    class PerspectiveCamera final : public Camera
    {
    public:
        PerspectiveCamera(float fov, float width, float height, float nearClip = 0.1f, float farClip = 1000.0f);

        void SetSize(float width, float height);

        void SetFov(const float fov)
        {
            m_FOV = fov;
            RecalculateViewMatrix();
        }

        void SetPosition(const glm::vec3 &position)
        {
            m_Position = position;
            RecalculateViewMatrix();
        }

        void SetRotation(const glm::vec3 &rotation)
        {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

        [[nodiscard]] const glm::vec3 &GetPosition() const { return m_Position; }
        [[nodiscard]] const glm::vec3 &GetRotation() const { return m_Rotation; }

        [[nodiscard]] const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
        [[nodiscard]] const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
        [[nodiscard]] glm::mat4 GetViewProjectionMatrix() const override { return m_ProjectionMatrix * m_ViewMatrix; }

    private:
        void RecalculateViewMatrix();

        void RecalculateProjectionMatrix();

        glm::mat4 m_ViewMatrix{1.0f};
        glm::mat4 m_ProjectionMatrix{1.0f};

        glm::vec3 m_Position{0.0f, 0.0f, 3.0f};
        glm::vec3 m_Rotation{0.0f};

        float m_FOV;
        float m_AspectRatio;
        float m_NearClip;
        float m_FarClip;
    };
}

#endif
