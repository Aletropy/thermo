#include "ThermoPch.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace Thermo
{
    static bool s_glfwInitialized = false;

    Window::Window(int width, int height, const std::string &title)
    {
        if(!s_glfwInitialized)
        {
            if(!glfwInit())
            {
                Logger::Log("Cannot initialize glfw!");
            }

            s_glfwInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
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