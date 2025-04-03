#include "SceneLayer.h"

#include "PathHelper.h"
#include "ECS/DefaultComponents/QuadRendererComponent.h"
#include "ECS/DefaultComponents/TransformComponent.h"

#define TESTE printf("teste");

namespace ThermoEditor
{
    SceneLayer *SceneLayer::s_Instance = nullptr;

    SceneLayer::SceneLayer()
    {
        s_Instance = this;
        Batch2D::Initialize();

        m_Framebuffer = Framebuffer::Create(1, 1);
        m_EditorCamera = CreateRef<OrthographicCamera>(1, 1);
        m_EditorCameraPerspective = CreateRef<PerspectiveCamera>(70, 1, 1);

        m_EditorCameraPerspective->SetPosition({0.0f, 0.0f, 5.0f});

        Batch2D::SetCamera(m_EditorCamera);

        m_World = World::LoadOrCreate(PathHelper::GetWorldPath("New World"));
    }

    void SceneLayer::OnAttach()
    {
        m_World->Initialize();
    }

    void SceneLayer::OnUpdate(const float deltaTime)
    {
        if (m_IsPlayMode)
            m_World->Update(deltaTime);

        m_Framebuffer->Bind();
        Renderer::SetClearColor(Colors::BLACK);
        Renderer::Clear();
        Batch2D::BeginBatch();

        const auto &registry = m_World->GetEntityManager()->GetRegistry();

        const auto &quadView = registry.view<const TransformComponent, QuadRendererComponent>();

        for (auto [entity, transform, renderer]: quadView.each())
        {
            const auto [pos, scale, rot] = transform;
            if (renderer.Texture == nullptr)
                Batch2D::PushQuad(pos, scale, rot.z, renderer.Color);
            else
                Batch2D::PushQuad(pos, scale, rot.x, renderer.Texture, 1.0f, renderer.Color);
        }

        Batch2D::EndBatch();
        Framebuffer::Unbind();
    }

    void SceneLayer::UpdatePlayMode()
    {
        if (m_IsPlayMode)
            m_World = World::LoadFromFile(PathHelper::GetWorldPath(m_World->GetDebugName()));
        else
            m_World->SaveToFile(PathHelper::GetCurrentWorldsPath());

        THERMO_LOG("PlayMode: %s", m_IsPlayMode ? "Disabled" : "Enabled");

        m_IsPlayMode = !m_IsPlayMode;

        auto title = std::string("Thermo Editor");
        if (m_IsPlayMode)
            title += " (Play)";
        Application::Instance->ChangeWindowName(title);
    }
} // ThermoEditor
