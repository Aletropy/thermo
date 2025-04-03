#ifndef MAIN_LAYER_H
#define MAIN_LAYER_H

#include <filesystem>
#include <Thermo.h>

using namespace Thermo;

static int WIDTH = 1280, HEIGHT = 720;

namespace ThermoEditor
{
    class EditorLayer final : public Layer
    {
    public:
        EditorLayer(const Ref<OrthographicCamera> &camera, const Ref<PerspectiveCamera> &perspCamera,
                    const Ref<Framebuffer> &framebuffer);

        void OnAttach() override;

        void OnUpdate(float deltaTime) override;

        void OnEvent(Event &event) override;

        static bool OnWindowClose(WindowCloseEvent &event);

    private:
        Ref<OrthographicCamera> m_OrthoCamera;
        Ref<PerspectiveCamera> m_PerspectiveCamera;
        Ref<Framebuffer> m_EditorFramebuffer;
        float m_ZoomFactor = 5.0f;
    };
} // ThermoEditor

#endif
