#include "HierarchyPanel.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "glm/gtc/type_ptr.inl"

namespace ThermoEditor
{
    static EntityId s_SelectedEntity = entt::null;

    void HierarchyPanel::DisplayEntities(const Ref<EntityManager> &entityManager)
    {
        ImGui::Begin("Hierarchy");

        for (const auto entities = entityManager->GetEntities(); const auto entity: entities)
        {
            const auto [Name] = entityManager->GetComponent<NameComponent>(entity);
            const auto label = Name.empty() ? "##" : Name.data();
            if (const bool isSelected = (entity == s_SelectedEntity); ImGui::Selectable(label, isSelected))
            {
                s_SelectedEntity = entity;
            }
        }

        ImGui::Separator();

        if (ImGui::Button("Create Entity"))
        {
            const auto newEntity = entityManager->CreateEntity();
            entityManager->AddComponent<TransformComponent>(newEntity);
            entityManager->AddComponent<NameComponent>(newEntity, std::string("New Entity"));
        }

        ImGui::End();

        ImGui::Begin("Components");

        if (s_SelectedEntity == entt::null)
        {
            ImGui::End();
            return;
        }

        auto &[Name] = entityManager->GetComponent<NameComponent>(s_SelectedEntity);
        ImGui::InputText("##", &Name);

        ImGui::SameLine();

        if (ImGui::Button("Remove Entity"))
        {
            entityManager->DestroyEntity(s_SelectedEntity);
            s_SelectedEntity = entt::null;
            ImGui::End();
            return;
        }

        ImGui::Separator();
        const auto entity = static_cast<entt::entity>(s_SelectedEntity);
        const auto &registry = entityManager->GetRegistry();

        if (registry.all_of<TransformComponent>(entity))
        {
            if (ImGui::TreeNode("Transform"))
            {
                auto &[Position, Scale, Rotation] = entityManager->GetComponent<TransformComponent>(s_SelectedEntity);

                ImGui::DragFloat3("Position", value_ptr(Position), 0.1f);
                ImGui::DragFloat3("Scale", value_ptr(Scale), 0.1f);
                ImGui::DragFloat3("Rotation", value_ptr(Rotation), 0.1f);

                if (ImGui::Button("Remove"))
                {
                    entityManager->RemoveComponent<TransformComponent>(s_SelectedEntity);
                    ImGui::TreePop();
                    goto EndProperties;
                }
                ImGui::TreePop();
            }
        }

        if (registry.all_of<QuadRendererComponent>(entity))
        {
            if (ImGui::TreeNode("Quad Renderer"))
            {
                auto &[Color] = entityManager->GetComponent<QuadRendererComponent>(s_SelectedEntity);

                ImGui::ColorEdit4("Color", value_ptr(Color));

                if (ImGui::Button("Remove"))
                {
                    entityManager->RemoveComponent<QuadRendererComponent>(s_SelectedEntity);
                    ImGui::TreePop();
                    goto EndProperties;
                }
                ImGui::TreePop();
            }
        }
    EndProperties:

        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup"))
        {
            if (!registry.all_of<TransformComponent>(entity))
                if (ImGui::MenuItem("Transform"))
                    entityManager->AddComponent<TransformComponent>(s_SelectedEntity);

            if (!registry.all_of<QuadRendererComponent>(entity))
                if (ImGui::MenuItem("Quad Renderer"))
                    entityManager->AddComponent<QuadRendererComponent>(s_SelectedEntity);

            ImGui::EndPopup();
        }

        ImGui::End();
    }
} // ThermoEditor
