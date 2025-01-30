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

        void OnUpdate(float deltaTime) override;

        [[nodiscard]] const Ref<Framebuffer> &GetFramebuffer() const { return m_Framebuffer; }
        [[nodiscard]] const Ref<Camera2D> &GetEditorCamera() const { return m_EditorCamera; }
        [[nodiscard]] const Ref<EntityManager> &GetEntityManager() const { return m_EntityManager; }

    private:
        Ref<Framebuffer> m_Framebuffer;
        Ref<Camera2D> m_EditorCamera;
        Ref<EntityManager> m_EntityManager;
    };
} // ThermoEditor

#endif //SCENELAYER_H
