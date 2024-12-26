#ifndef THERMOENGINE_APPLICATION_H
#define THERMOENGINE_APPLICATION_H

#include "Graphics/Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"

namespace Thermo
{
    struct WindowAppSpecification
    {
        int WindowWidth;
        int WindowHeight;
        std::string WindowTitle;
        bool VSync;
    };

    class Application
    {
    public:
        static Application* Instance;
    public:
        explicit Application(const WindowAppSpecification& spec);

        void Run();
        void Terminate();

        template<typename T, typename ... Args>
        void PushLayer(Args&& ... args)
        {
            m_LayerStack.PushLayer<T>();
        }

        template<typename T, typename ... Args>
        void PushOverlay(Args&& ... args)
        {
            m_LayerStack.PushOverlay<T>();
        }

        const Window& GetWindow() { return m_Window; }

        void OnEvent(Event& event);

    private:
        Window m_Window;
        LayerStack m_LayerStack;

        bool m_IsRunning = true;
        WindowAppSpecification m_Spec;

    };
    static Application* CreateDefaultApplication();
} // Thermo

#endif //THERMOENGINE_APPLICATION_H
