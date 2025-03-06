#include "SceneLayer.h"

#include "ECS/DefaultComponents/QuadRendererComponent.h"
#include "ECS/DefaultComponents/TransformComponent.h"

namespace ThermoEditor
{
    SceneLayer::SceneLayer()
    {
        Batch2D::Initialize();

        m_Framebuffer = Framebuffer::Create(1, 1);
        m_SystemManager = std::make_shared<SystemManager>();

        m_EditorCamera = CreateRef<OrthographicCamera>(1, 1);
        m_EditorCameraPerspective = CreateRef<PerspectiveCamera>(70, 1, 1);

        m_EditorCameraPerspective->SetPosition({0.0f, 0.0f, 5.0f});

        Batch2D::SetCamera(m_EditorCameraPerspective);

        m_EntityManager = CreateRef<EntityManager>();

        m_Spritesheet = CreateRef<Spritesheet>("assets/textures/test.png", 16, 16, 2, 1);
    }

    void SceneLayer::OnAttach()
    {
        m_SystemManager->InitializeSystems();
    }

    void SceneLayer::OnUpdate(const float deltaTime)
    {
        m_SystemManager->UpdateSystems(deltaTime);

        m_Framebuffer->Bind();
        Renderer::SetClearColor(Colors::BLACK);
        Renderer::Clear();
        Batch2D::BeginBatch();

        // ReSharper disable once CppTooWideScopeInitStatement
        const auto &view = m_EntityManager->GetRegistry().view<const TransformComponent, QuadRendererComponent>();
        for (auto [entity, transform, renderer]: view.each())
        {
            const auto [pos, scale, rot] = transform;
            Batch2D::PushQuad(pos, scale, rot.z, renderer.Color);
        }

        Batch2D::EndBatch();
        Framebuffer::Unbind();
    }
} // ThermoEditor
