#include "ThermoPch.h"
#include "Application.h"

#include "Core/Time.h"
#include "Layers/ImGuiLayer.h"

namespace Thermo
{
    Application *Application::Instance = nullptr;

    Application::Application(const WindowAppSpecification &spec)
        : m_Spec(spec), m_Window(spec.WindowWidth, spec.WindowHeight, spec.WindowTitle)
    {
        THERMO_ASSERT(Instance == nullptr, "%s", "Application already exists!");
        Instance = this;

        m_LayerStack.PushOverlay<ImGuiLayer>();
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            const float deltaTime = Time::CalculateDeltaTime();

            ProcessEvents();

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

    void Application::ProcessEvents()
    {
        std::queue<std::unique_ptr<Event> > events; {
            std::lock_guard<std::mutex> lock(m_EventMutex);
            std::swap(events, m_EventQueue);
        }

        while (!events.empty())
        {
            auto &event = events.front();
            m_LayerStack.OnEvent(*event);
            events.pop();
        }
    }

    void Application::OnEvent(Event &event)
    {
        std::lock_guard<std::mutex> lock(m_EventMutex);
        m_EventQueue.push(event.Clone());
    }
} // Thermo
