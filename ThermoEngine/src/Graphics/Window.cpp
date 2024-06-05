#include "ThermoPch.h"
#include "Window.h"

#include "Graphics/Rendering/Renderer.h"
#include <GLFW/glfw3.h>

#include "Application/Application.h"

namespace Thermo
{
    static bool s_glfwInitialized = false;

    Window::Window(int width, int height, const std::string &title)
    {
        if(!s_glfwInitialized)
        {
            THERMO_ASSERT(glfwInit(), "%s", "Failed to initialize GLFW!");
            s_glfwInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        Renderer::Initialize();

        THERMO_LOG("Window created: %s(%d, %d)", title.c_str(), width, height);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            Application::Instance->Terminate();
        });
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
    }

    void Window::UpdateWindow()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    bool Window::IsClosed() const
    {
        return glfwWindowShouldClose(m_Window);
    }
} // Thermo