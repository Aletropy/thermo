#include "ThermoPch.h"
#include "Window.h"

#include "Graphics/Rendering/Renderer.h"
#include <GLFW/glfw3.h>

#include "Application/Application.h"
#include "Events/WindowEvents.h"

namespace Thermo
{
    static bool s_glfwInitialized = false;

    Window::Window(const int width, const int height, const std::string &title)
    {
        if(!s_glfwInitialized)
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

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            auto event = WindowCloseEvent();
            Application::Instance->OnEvent(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int w, int h)
        {
           auto event = WindowResizeEvent(w, h);
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