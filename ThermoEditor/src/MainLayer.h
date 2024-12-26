#ifndef MAIN_LAYER_H
#define MAIN_LAYER_H

#include <Thermo.h>

#include "Events/WindowEvents.h"

using namespace Thermo;

static int WIDTH = 1280, HEIGHT = 720;

namespace ThermoEditor
{
    struct Transform
    {
        glm::vec2 Position = { 0.0f, 0.0f };
        glm::vec2 Scale = { 1.0f, 1.0f };
        float Rotation = 0.0f;
        glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    };


    class MainLayer : public Layer
    {
    public:
        void OnAttach() override;
        void CreateSquare() const;
        void OnUpdate(float deltaTime) override;
        void OnEvent(Event& event) override;

        bool OnWindowResize(WindowResizeEvent& event) const;

        static bool OnWindowClose(WindowCloseEvent &event);

    private:
        Ref<Camera2D> m_Camera;
        Ref<EntityManager> m_EntityManager;
    };

} // ThermoEditor

#endif