#ifndef MAIN_LAYER_H
#define MAIN_LAYER_H

#include <Thermo.h>

using namespace Thermo;

static int WIDTH = 1280, HEIGHT = 720;

namespace ThermoEditor
{
    class EditorLayer final : public Layer
    {
    public:
        EditorLayer(const Ref<Camera2D> &camera, const Ref<EntityManager> &entityManager,
                    const Ref<Framebuffer> &framebuffer);

        void OnUpdate(float deltaTime) override;

        void OnEvent(Event &event) override;

        static bool OnWindowClose(WindowCloseEvent &event);

    private:
        Ref<Camera2D> m_Camera;
        Ref<EntityManager> m_EntityManager;
        Ref<Framebuffer> m_EditorFramebuffer;
    };
} // ThermoEditor

#endif
