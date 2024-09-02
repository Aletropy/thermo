#include "ThermoPch.h"
#include "Application.h"

#include "Core/Time.h"
#include "ECS/Systems/ImGuiSystem.h"

namespace Thermo
{
    Application* Application::Instance = nullptr;

    Application::Application(const ApplicationSpecification &spec)
        : m_Spec(spec), m_Window(spec.WindowWidth, spec.WindowHeight, spec.WindowTitle)
    {
        THERMO_ASSERT(Instance == nullptr, "%s", "Application already exists!");
        Instance = this;

        m_SystemManager.PushOverlay<ImGuiSystem>();
    }

    void Application::Run()
    {
        m_SystemManager.InitializeSystems();

        while(m_IsRunning)
        {
            float deltaTime = Time::CalculateDeltaTime();

            ImGuiSystem::Start();

            m_SystemManager.UpdateSystems(deltaTime);

            ImGuiSystem::End();

            m_Window.UpdateWindow();
        }
    }

    void Application::Terminate()
    {
        m_IsRunning = false;
    }
} // Thermo