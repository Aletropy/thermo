#ifndef SCENELAYER_H
#define SCENELAYER_H

#include <Thermo.h>

#include "ECS/World.h"

using namespace Thermo;

namespace ThermoEditor
{
    class SceneLayer final : public Layer
    {
    public:
        SceneLayer();

        void OnAttach() override;

        void OnUpdate(float deltaTime) override;

        [[nodiscard]] const Ref<Framebuffer> &GetFramebuffer() const { return m_Framebuffer; }
        [[nodiscard]] const Ref<OrthographicCamera> &GetEditorCamera() const { return m_EditorCamera; }

        [[nodiscard]] const Ref<PerspectiveCamera> &GetEditorCameraPerspective() const
        {
            return m_EditorCameraPerspective;
        }

        [[nodiscard]] const Ref<World> &GetWorld() const { return m_World; }

        void UpdatePlayMode();

        bool IsInPlayMode() const { return m_IsPlayMode; }

        static SceneLayer *Get() { return s_Instance; }

    private:
        Ref<Framebuffer> m_Framebuffer;
        bool m_IsPlayMode = false;
        Ref<OrthographicCamera> m_EditorCamera;
        Ref<PerspectiveCamera> m_EditorCameraPerspective;
        Ref<World> m_World;

        static SceneLayer *s_Instance;
    };
} // ThermoEditor

#endif //SCENELAYER_H
