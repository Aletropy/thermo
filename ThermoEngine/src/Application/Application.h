#ifndef THERMOENGINE_APPLICATION_H
#define THERMOENGINE_APPLICATION_H

#include "Graphics/Window.h"
#include "ECS/SystemManager.h"
#include "ECS/Systems/ImGuiSystem.h"

namespace Thermo
{
    struct ApplicationSpecification
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
        explicit Application(const ApplicationSpecification& spec);

        void Run();
        void Terminate();

        template<typename T>
        void PushSystem()
        {
            m_SystemManager.PushSystem<T>();
        }

        const Window& GetWindow() { return m_Window; }

    private:
        Window m_Window;
        SystemManager m_SystemManager;

        bool m_IsRunning = true;
        ApplicationSpecification m_Spec;

    };
    static Application* CreateDefaultApplication();
} // Thermo

#endif //THERMOENGINE_APPLICATION_H
