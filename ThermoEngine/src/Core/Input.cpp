#include "ThermoPch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

#include "Application/Application.h"

namespace Thermo
{
    bool Input::IsKeyPressed(const Keys key)
    {
        const auto window = Application::Instance->GetWindow().GetHandle();
        return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(const Keys button)
    {
        const auto window = Application::Instance->GetWindow().GetHandle();
        return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition()
    {
        const auto window = Application::Instance->GetWindow().GetHandle();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(
            static_cast<float>(x),
            static_cast<float>(y));
    }
} // Thermo
