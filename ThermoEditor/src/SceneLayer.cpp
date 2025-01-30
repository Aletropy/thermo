#include "SceneLayer.h"

namespace ThermoEditor
{
    SceneLayer::SceneLayer()
    {
        Batch2D::Initialize();

        m_Framebuffer = Framebuffer::Create(1, 1);

        m_EditorCamera = CreateRef<Camera2D>(1, 1);
        Batch2D::SetCamera(m_EditorCamera);

        m_EntityManager = CreateRef<EntityManager>();
    }

    void SceneLayer::OnUpdate(float deltaTime)
    {
        m_Framebuffer->Bind();
        Renderer::Clear();
        Batch2D::BeginBatch();
        Batch2D::PushQuad({0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f);
        Batch2D::EndBatch();

        Framebuffer::Unbind();
    }
} // ThermoEditor
