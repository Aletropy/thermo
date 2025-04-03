#include "HierarchyPanel.h"

#include <filesystem>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "SceneLayer.h"
#include "ECS/DefaultComponents/CameraComponent.h"
#include "glm/gtc/type_ptr.inl"

namespace ThermoEditor
{
    static EntityId s_SelectedEntity = entt::null;

    static bool s_isRenaming = false;
    static char s_RenameBuffer[128] = "";

    void HierarchyPanel::DisplayEntities(const Ref<EntityManager> &entityManager)
    {
        ImGui::Begin("Hierarchy");

        for (const auto entities = entityManager->GetEntities(); const auto entity: entities)
        {
            auto &[Name] = entityManager->GetComponent<NameComponent>(entity);
            const auto label = Name.empty() ? "##" : Name.data();

            ImGui::PushID(static_cast<int>(entity));

            if (s_isRenaming && s_SelectedEntity == entity)
            {
                ImGui::SetKeyboardFocusHere();

                ImGui::PushItemWidth(150);
                if (ImGui::InputText("##Rename", s_RenameBuffer, IM_ARRAYSIZE(s_RenameBuffer),
                                     ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    Name = std::string(s_RenameBuffer);
                    s_isRenaming = false;
                }
                ImGui::PopItemWidth();
            } else
            {
                if (const bool isSelected = (entity == s_SelectedEntity); ImGui::Selectable(label, isSelected))
                {
                    s_SelectedEntity = entity;
                }
            }

            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Duplicate"))
                {
                }

                if (ImGui::MenuItem("Delete"))
                {
                    entityManager->DestroyEntity(entity);
                    if (s_SelectedEntity == entity)
                        s_SelectedEntity = entt::null;
                }

                ImGui::EndPopup();
            }

            ImGui::PopID();
        }

        if (s_SelectedEntity != entt::null)
        {
            if (ImGui::IsKeyPressed(ImGuiKey_F2))
            {
                auto &[Name] = entityManager->GetComponent<NameComponent>(s_SelectedEntity);

                s_isRenaming = true;
                strncpy(s_RenameBuffer, Name.c_str(), sizeof(s_RenameBuffer));
                s_RenameBuffer[sizeof(s_RenameBuffer) - 1] = '\0';
            }
        }

        if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Create Empty"))
            {
                const auto newEntity = entityManager->CreateEntity();

                entityManager->AddComponent<TransformComponent>(newEntity);
                entityManager->AddComponent<NameComponent>(newEntity, "New Empty Entity");
            }

            if (ImGui::MenuItem("Create Quad"))
            {
                const auto newEntity = entityManager->CreateEntity();

                entityManager->AddComponent<TransformComponent>(newEntity);
                entityManager->AddComponent<QuadRendererComponent>(newEntity);
                entityManager->AddComponent<NameComponent>(newEntity, "New Empty Entity");
            }

            ImGui::EndPopup();
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Delete) && ImGui::IsWindowHovered())
        {
            if (s_SelectedEntity != entt::null)
            {
                entityManager->DestroyEntity(s_SelectedEntity);
                s_SelectedEntity = entt::null;
            }
        }

        ImGui::End();

        ImGui::Begin("Properties");

        if (s_SelectedEntity == entt::null)
        {
            ImGui::End();
            return;
        }

        auto nameComponent = entityManager->GetRegistry().try_get<NameComponent>(
            static_cast<entt::entity>(s_SelectedEntity));

        if (nameComponent != nullptr)
        {
            auto &[Name] = *nameComponent;
            ImGui::InputText("##", &Name);
        }


        ImGui::Separator();

        const auto entity = static_cast<entt::entity>(s_SelectedEntity);
        const auto &enttRegistry = entityManager->GetRegistry();

        const auto &components = entityManager->GetAllComponents(s_SelectedEntity);

        for (const auto &[typeId, wrapper]: components)
        {
            auto it = GetComponentRegistry().find(typeId);
            if (it == GetComponentRegistry().end())
                continue;
            auto registry = it->second;

            ImGui::Text(registry.name.c_str());

            ImGui::Separator();

            for (const auto &[name, type, offset]: registry.properties)
            {
                const auto base = static_cast<char *>(wrapper.data);
                const auto propPtr = static_cast<void *>(base + offset);

                if (type == PropertyType::Integer)
                {
                    const auto value = static_cast<int *>(propPtr);
                    ImGui::DragInt(name.c_str(), value, 0.5f);
                }

                if (type == PropertyType::Float)
                {
                    const auto value = static_cast<float *>(propPtr);
                    ImGui::DragFloat(name.c_str(), value, 0.1f, 0.f, 100000.0f, "%.1f");
                }

                if (type == PropertyType::Color)
                {
                    const auto value = static_cast<float *>(propPtr);
                    ImGui::ColorEdit4(name.c_str(), value);
                }

                if (type == PropertyType::TexturePtr)
                {
                    auto value = *static_cast<Ref<Texture2D> *>(propPtr);

                    char pathBuffer[1024] = "Insert file path or drop an image here.";

                    if (value != nullptr)
                        strcpy(pathBuffer, value->GetFilepath().c_str());

                    if (ImGui::InputText("Texture", pathBuffer, 1024))
                    {
                        std::filesystem::path path(pathBuffer);
                        *static_cast<Ref<Texture2D> *>(propPtr) =
                                exists(path) && !is_directory(path) ? Texture2D::Create(path.string()) : nullptr;
                    }

                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("IMAGE"))
                        {
                            auto droppedPath = static_cast<const char *>(payload->Data);
                            std::filesystem::path path(droppedPath);
                            if (!is_directory(path) && exists(path))
                                *static_cast<Ref<Texture2D> *>(propPtr) = Texture2D::Create(path);
                        }
                        ImGui::EndDragDropTarget();
                    }
                }

                if (type == PropertyType::Vector3)
                {
                    const auto value = static_cast<float *>(propPtr);
                    ImGui::DragFloat3(name.c_str(), value, 0.1f);
                }
            }

            ImGui::Separator();
        }

    EndProperties:
        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup"))
        {
            auto &registry = SerializerRegistry::GetRegistry();
            for (const auto &serializer: registry | std::views::values)
            {
                if (ImGui::MenuItem(serializer->GetComponentName()))
                    serializer->CreateNew(entityManager, s_SelectedEntity);
            }

            ImGui::EndPopup();
        }

        ImGui::End();
    }
} // ThermoEditor
