#include "EditorLayer.h"
#include <../../vendor/imgui/imgui.h>

#include "imgui_internal.h"
#include "glm/gtc/type_ptr.hpp"
#include "GUI/ExplorerPanel.h"
#include "GUI/HierarchyPanel.h"

namespace ThermoEditor
{
    EditorLayer::EditorLayer(const Ref<OrthographicCamera> &camera, const Ref<PerspectiveCamera> &perspCamera,
                             const Ref<EntityManager> &entityManager,
                             const Ref<Framebuffer> &framebuffer)
        : m_OrthoCamera(camera), m_EntityManager(entityManager), m_EditorFramebuffer(framebuffer),
          m_PerspectiveCamera(perspCamera)
    {
    }

    static bool needsResize = false;

    static auto cameraPosition = glm::vec3(0.0f);
    static auto cameraRotation = glm::vec3(0.0f);

    void EditorLayer::OnUpdate(float deltaTime)
    {
        ExplorerPanel::DisplayExplorerPanel();
        HierarchyPanel::DisplayEntities(m_EntityManager);

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
        Application::Instance->Terminate();
        return true;
    }
}
