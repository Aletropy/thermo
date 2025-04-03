#include "ThermoPch.h"
#include "Application.h"

#include "Core/Time.h"
#include "ECS/DefaultComponents/CameraComponent.h"
#include "ECS/DefaultComponents/NameComponent.h"
#include "ECS/DefaultComponents/NextageComponent.h"
#include "ECS/DefaultComponents/QuadRendererComponent.h"
#include "ECS/DefaultComponents/TransformComponent.h"
#include "ECS/Serialization/SerializerRegistry.h"
#include "Layers/ImGuiLayer.h"

namespace Thermo
{
    Application *Application::Instance = nullptr;

    Application::Application(const WindowAppSpecification &spec)
        : m_Spec(spec), m_Window(spec.WindowWidth, spec.WindowHeight, spec.WindowTitle)
    {
        THERMO_ASSERT(Instance == nullptr, "%s", "Application already exists!");
        Instance = this;

        SerializerRegistry::RegisterComponentSerializer<NameComponent>(
            typeid(NameComponent).hash_code());
        SerializerRegistry::RegisterComponentSerializer<QuadRendererComponent>(
            typeid(QuadRendererComponent).hash_code());
        SerializerRegistry::RegisterComponentSerializer<TransformComponent>(
            typeid(TransformComponent).hash_code());
        SerializerRegistry::RegisterComponentSerializer<CameraComponent>(
            typeid(CameraComponent).hash_code());

        SerializerRegistry::RegisterComponentSerializer<NextageComponent>(
            typeid(NextageComponent).hash_code());

#ifndef NOT_USING_IM_GUI
        m_LayerStack.PushOverlay<ImGuiLayer>();
#endif
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            const float deltaTime = Time::CalculateDeltaTime();

            ProcessEvents();

#ifndef NOT_USING_IM_GUI
            ImGuiLayer::Start();
#endif
            m_LayerStack.UpdateLayers(deltaTime);
#ifndef NOT_USING_IM_GUI
            ImGuiLayer::End();
#endif

            m_Window.UpdateWindow();
        }
    }

    void Application::Terminate()
    {
        m_IsRunning = false;
    }

    void Application::ChangeWindowName(const std::string &newName)
    {
        m_Spec.WindowTitle = newName;
        m_Window.SetName(newName);
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
