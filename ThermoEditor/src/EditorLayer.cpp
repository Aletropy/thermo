#include "EditorLayer.h"
#include <../../vendor/imgui/imgui.h>

#include "imgui_internal.h"

namespace ThermoEditor
{
    EditorLayer::EditorLayer(const Ref<Camera2D> &camera, const Ref<EntityManager> &entityManager,
                             const Ref<Framebuffer> &framebuffer)
        : m_Camera(camera), m_EntityManager(entityManager), m_EditorFramebuffer(framebuffer)
    {
    }

    static bool needsResize = false;

    void EditorLayer::OnUpdate(float deltaTime)
    {
        ImGui::Begin("Hierarchy");

        ImGui::Separator();

        ImGui::End(); // Hierarchy

        ImGui::Begin("Viewport");

        const float newWidth = ImGui::GetContentRegionAvail().x;
        const float newHeight = ImGui::GetContentRegionAvail().y;

        if (needsResize)
        {
            m_EditorFramebuffer->Invalidate(static_cast<int>(newWidth), static_cast<int>(newHeight));

            Renderer::SetViewport(0, 0, static_cast<uint32_t>(newWidth), static_cast<uint32_t>(newHeight));
            m_Camera->SetSize(newWidth, newHeight);

            needsResize = false;
        }

        if (static_cast<int>(newWidth) != m_EditorFramebuffer->GetWidth() ||
            static_cast<int>(newHeight) != m_EditorFramebuffer->GetHeight())
        {
            needsResize = true;
        }

        const auto pos = ImGui::GetCurrentWindow()->Pos;

        ImGui::GetWindowDrawList()->AddImage(
            reinterpret_cast<void *>(m_EditorFramebuffer->GetColorAttachment()),
            ImVec2(pos.x, pos.y),
            ImVec2(pos.x + newWidth, pos.y + newHeight),
            ImVec2(0, 1), ImVec2(1, 0)
        );

        ImGui::End(); // Viewport
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
