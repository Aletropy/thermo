#include "EditorLayer.h"
#include <../../vendor/imgui/imgui.h>

#include <utility>

#include "imgui_internal.h"
#include "PathHelper.h"
#include "SceneLayer.h"
#include "Core/Project.h"
#include "glm/gtc/type_ptr.hpp"
#include "GUI/ExplorerPanel.h"
#include "GUI/HierarchyPanel.h"
#include "GUI/ProjectPanel.h"

namespace ThermoEditor
{
    EditorLayer::EditorLayer(const Ref<OrthographicCamera> &camera,
                             const Ref<PerspectiveCamera> &perspCamera,
                             const Ref<Framebuffer> &framebuffer)
        : m_OrthoCamera(camera), m_PerspectiveCamera(perspCamera),
          m_EditorFramebuffer(framebuffer)
    {
    }

    void EditorLayer::OnAttach()
    {
        ExplorerPanel::Load(PathHelper::GetCurrentRootPath());
    }

    static bool needsResize = false;

    void EditorLayer::OnUpdate(const float deltaTime)
    {
        const auto m_World = SceneLayer::Get()->GetWorld();
        const auto m_EntityManager = m_World->GetEntityManager();

        if (ImGui::IsKeyPressed(ImGuiKey_S, false) && !SceneLayer::Get()->IsInPlayMode())
        {
            if (ImGui::IsKeyDown(ImGuiKey_ModCtrl))
            {
                m_World->SaveToFile(PathHelper::GetCurrentWorldsPath());
                Project::Instance.SaveProject();
            }
        }

        if (ImGui::IsKeyPressed(ImGuiKey_F5, false))
        {
            const auto sceneLayer = SceneLayer::Get();
            sceneLayer->UpdatePlayMode();
        }

        ExplorerPanel::DisplayExplorerPanel();
        HierarchyPanel::DisplayEntities(m_EntityManager);

        ProjectPanel::RenderProjectPanel();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        ImGui::Begin("Viewport");

        const float newWidth = ImGui::GetContentRegionAvail().x;
        const float newHeight = ImGui::GetContentRegionAvail().y;

        const auto pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            reinterpret_cast<void *>(m_EditorFramebuffer->GetColorAttachment()),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + newWidth, pos.y + newHeight),
            ImVec2(0, 1), ImVec2(1, 0)
        );

        if (needsResize)
        {
            m_EditorFramebuffer->Invalidate(static_cast<int>(newWidth), static_cast<int>(newHeight));

            Renderer::SetViewport(0, 0, static_cast<uint32_t>(newWidth), static_cast<uint32_t>(newHeight));

            m_OrthoCamera->SetSize(newWidth, newHeight);
            m_PerspectiveCamera->SetSize(newWidth, newHeight);

            needsResize = false;
        }

        if (static_cast<int>(newWidth) != m_EditorFramebuffer->GetWidth() ||
            static_cast<int>(newHeight) != m_EditorFramebuffer->GetHeight())
        {
            needsResize = true;
        }

        if (ImGui::IsWindowHovered())
        {
            const ImGuiIO &io = ImGui::GetIO();
            if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
            {
                ImGui::CaptureMouseFromApp(true);
                glm::vec3 camPos = m_OrthoCamera->GetPosition();
                float panSpeed = (0.1f * m_ZoomFactor) * deltaTime;
                if (ImGui::IsKeyDown(ImGuiKey_ModCtrl))
                    panSpeed *= 2.5f;
                camPos.x -= io.MouseDelta.x * panSpeed;
                camPos.y += io.MouseDelta.y * panSpeed;
                m_OrthoCamera->SetPosition(camPos);
            } else
                ImGui::CaptureMouseFromApp(false);

            if (io.MouseWheel != 0.0f)
            {
                float zoomSpeed = 5.0f;
                if (ImGui::IsKeyDown(ImGuiKey_ModCtrl))
                {
                    zoomSpeed = 10.0f;
                }
                m_ZoomFactor -= (io.MouseWheel * zoomSpeed) * deltaTime;
                m_ZoomFactor = glm::max(m_ZoomFactor, 0.1f); // Ensure zoom factor doesn't go below 0.1
                m_OrthoCamera->SetZoom(m_ZoomFactor);
            }
        }

        ImGui::End(); // Viewport
        ImGui::PopStyleVar();
    }

    void EditorLayer::OnEvent(Event &event)
    {
        auto dispatcher = EventDispatcher{event};
        dispatcher.Dispatch<WindowCloseEvent>(THERMO_BIND_EVENT_FN(EditorLayer::OnWindowClose));
    }

    bool EditorLayer::OnWindowClose(WindowCloseEvent &event)
    {
        const auto sceneLayer = SceneLayer::Get();
        if (sceneLayer != nullptr)
            sceneLayer->GetWorld()->SaveToFile(PathHelper::GetCurrentWorldsPath());
        Application::Instance->Terminate();
        return true;
    }
}
