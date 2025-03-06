#ifndef SCENELAYER_H
#define SCENELAYER_H

#include <Thermo.h>

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

        [[nodiscard]] const Ref<EntityManager> &GetEntityManager() const { return m_EntityManager; }

    private:
        Ref<Framebuffer> m_Framebuffer;
        Ref<Spritesheet> m_Spritesheet;
        Ref<OrthographicCamera> m_EditorCamera;
        Ref<PerspectiveCamera> m_EditorCameraPerspective;
        Ref<EntityManager> m_EntityManager;
        Ref<SystemManager> m_SystemManager;
    };
} // ThermoEditor

#endif //SCENELAYER_H
