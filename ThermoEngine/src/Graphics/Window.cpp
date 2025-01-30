#include "ThermoPch.h"
#include "Window.h"

#include "Graphics/Rendering/Renderer.h"
#include <GLFW/glfw3.h>

#include "Application/Application.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

namespace Thermo
{
    static bool s_glfwInitialized = false;

    Window::Window(const int width, const int height, const std::string &title)
    {
        if (!s_glfwInitialized)
        {
            THERMO_ASSERT(glfwInit(), "%s", "Failed to initialize GLFW!");
            s_glfwInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_SAMPLES, 4);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        Renderer::Initialize();

        THERMO_LOG("Window created: %s(%d, %d)", title.c_str(), width, height);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
        {
            auto event = WindowCloseEvent();
            Application::Instance->OnEvent(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int w, int h)
        {
            auto event = WindowResizeEvent(w, h);
            Application::Instance->OnEvent(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            if (action == GLFW_RELEASE)
            {
                auto keyReleaseEvent = KeyReleasedEvent(key);
                Application::Instance->OnEvent(keyReleaseEvent);
            } else if (action == GLFW_PRESS)
            {
                auto keyPressedEvent = KeyPressedEvent(key, 1);
                Application::Instance->OnEvent(keyPressedEvent);
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xpos, double ypos)
        {
            auto event = MouseMovedEvent(xpos, ypos);
            Application::Instance->OnEvent(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
        {
            if (action == GLFW_RELEASE)
            {
                auto releaseEvent = MouseButtonReleasedEvent(button);
                Application::Instance->OnEvent(releaseEvent);
            } else if (action == GLFW_PRESS)
            {
                auto pressEvent = MouseButtonPressedEvent(button);
                Application::Instance->OnEvent(pressEvent);
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xoffset, double yoffset)
        {
            auto event = MouseScrolledEvent(xoffset, yoffset);
            Application::Instance->OnEvent(event);
        });
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
    }

    void Window::UpdateWindow() const
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    bool Window::IsClosed() const
    {
        return glfwWindowShouldClose(m_Window);
    }
} // Thermo
