#include "MainLayer.h"
#include <../../vendor/imgui/imgui.h>

namespace ThermoEditor
{
    void MainLayer::OnAttach()
    {
        Batch2D::Initialize();

        m_Camera = CreateRef<Camera2D>(WIDTH, HEIGHT, 5.0f);
        Batch2D::SetCamera(m_Camera);

        m_EntityManager = CreateRef<EntityManager>();

        m_ViewFramebuffer = Framebuffer::Create(800, 600);
    }

    void MainLayer::CreateSquare() const
    {
        const auto entity = m_EntityManager->CreateEntity();
        m_EntityManager->AddComponent<Transform>(entity, Transform{});
    }

    void MainLayer::OnUpdate(float deltaTime)
    {
        Renderer::Clear();

        ImGui::Begin("Hierarchy");
        if (ImGui::Button("Create Square"))
        {
            CreateSquare();
        }

        ImGui::Separator();

        const auto view = m_EntityManager->GetRegistry().view<Transform>();

        for (auto [entity, transform]: view.each())
        {
            ImGui::PushID(static_cast<int>(entity));

            ImGui::SeparatorText("Entity");
            ImGui::DragFloat2("Position", &transform.Position.x, 0.1f);
            ImGui::DragFloat2("Scale", &transform.Scale.x, 0.1f);
            ImGui::DragFloat("Rotation", &transform.Rotation, 0.1f);
            ImGui::ColorEdit4("Color", &transform.Color.x);

            ImGui::PopID();
        }

        ImGui::End(); // Hierarchy

        ImGui::Begin("Viewport");

        const float windowWidth = ImGui::GetContentRegionAvail().x;
        const float windowHeight = ImGui::GetContentRegionAvail().y;

        m_ViewFramebuffer->Invalidate(windowWidth, windowHeight);

        Renderer::SetViewport(
            0, 0,
            static_cast<uint32_t>(windowWidth), static_cast<uint32_t>(windowHeight)
            );
        m_Camera->SetSize(windowWidth, windowHeight);

        auto pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            reinterpret_cast<void *>(m_ViewFramebuffer->GetId()),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + windowWidth, pos.y + windowHeight),
            ImVec2(0, 1), ImVec2(1, 0)
            );

        ImGui::End(); // Viewport


        m_ViewFramebuffer->Bind();
        Batch2D::BeginBatch();
        for (auto [entity, transform]: view.each())
        {
            Batch2D::PushQuad(transform.Position, transform.Scale, transform.Rotation, transform.Color);
        }
        Batch2D::EndBatch();
        m_ViewFramebuffer->Unbind();
    }

    void MainLayer::OnEvent(Event &event)
    {
        auto dispatcher = EventDispatcher{event};
        dispatcher.Dispatch<WindowCloseEvent>(THERMO_BIND_EVENT_FN(MainLayer::OnWindowClose));
    }

    bool MainLayer::OnWindowClose(WindowCloseEvent& event)
    {
        Application::Instance->Terminate();
        return true;
    }
}
