#include "ThermoPch.h"
#include "Application.h"

namespace Thermo
{
    Application* Application::Instance = nullptr;

    Application::Application(const ApplicationSpecification &spec)
        : m_Spec(spec), m_Window(spec.WindowWidth, spec.WindowHeight, spec.WindowTitle)
    {
        THERMO_ASSERT(Instance == nullptr, "%s", "Application already exists!");
        Instance = this;
    }

    void Application::Run()
    {
        m_SystemManager.InitializeSystems();

        while(m_IsRunning)
        {
            m_SystemManager.UpdateSystems(0.0f);

            m_Window.UpdateWindow();
        }
    }

    void Application::Terminate()
    {
        m_IsRunning = false;
    }
} // Thermo