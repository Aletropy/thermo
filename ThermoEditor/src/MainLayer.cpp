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

        ImGui::End();

        Batch2D::BeginBatch();
        for (auto [entity, transform]: view.each())
        {
            Batch2D::PushQuad(transform.Position, transform.Scale, transform.Rotation, transform.Color);
        }
        Batch2D::EndBatch();
    }
}
