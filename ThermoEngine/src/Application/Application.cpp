#include "ThermoPch.h"
#include "Application.h"

#include "Core/Time.h"
#include "Layers/ImGuiLayer.h"

namespace Thermo
{
    Application* Application::Instance = nullptr;

    Application::Application(const WindowAppSpecification &spec)
        : m_Spec(spec), m_Window(spec.WindowWidth, spec.WindowHeight, spec.WindowTitle)
    {
        THERMO_ASSERT(Instance == nullptr, "%s", "Application already exists!");
        Instance = this;

        m_LayerStack.PushOverlay<ImGuiLayer>();
    }

    void Application::Run()
    {
        while(m_IsRunning)
        {
            const float deltaTime = Time::CalculateDeltaTime();

            ImGuiLayer::Start();
            m_LayerStack.UpdateLayers(deltaTime);
            ImGuiLayer::End();

            m_Window.UpdateWindow();
        }
    }

    void Application::Terminate()
    {
        m_IsRunning = false;
    }
} // Thermo