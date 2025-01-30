#ifndef THERMOENGINE_APPLICATION_H
#define THERMOENGINE_APPLICATION_H

#include <queue>

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
        static Application *Instance;

    public:
        explicit Application(const WindowAppSpecification &spec);

        void Run();

        void Terminate();

        template<typename T, typename... Args>
        Ref<T> PushLayer(Args &&... args)
        {
            return m_LayerStack.PushLayer<T>(std::forward<Args>(args)...);
        }

        template<typename T, typename... Args>
        Ref<T> PushOverlay(Args &&... args)
        {
            return m_LayerStack.PushOverlay<T>(std::forward<Args>(args)...);
        }

        const Window &GetWindow() { return m_Window; }

        void OnEvent(Event &event);

        void ProcessEvents();

    private:
        Window m_Window;
        LayerStack m_LayerStack;

        bool m_IsRunning = true;
        WindowAppSpecification m_Spec;

        std::queue<std::unique_ptr<Event> > m_EventQueue;
        std::mutex m_EventMutex;
    };

    static Application *CreateDefaultApplication();
} // Thermo

#endif //THERMOENGINE_APPLICATION_H
