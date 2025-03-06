#include "ThermoPch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "Application/Application.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Thermo
{
    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        SetupStyle();

        io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Bold.ttf", 16.0f);

        ImGui_ImplGlfw_InitForOpenGL(Application::Instance->GetWindow().GetHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImGuiLayer::Start()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
    }

    void ImGuiLayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::SetupStyle()
    {
        ImGuiStyle &style = ImGui::GetStyle();
        ImVec4 *colors = style.Colors;

        // -- Arredondamento e dimensões pra ficar suave --
        style.WindowRounding = 6.0f;
        style.FrameRounding = 6.0f;
        style.GrabRounding = 4.0f;
        style.PopupRounding = 6.0f;
        style.ScrollbarRounding = 6.0f;
        style.TabRounding = 6.0f;

        style.FrameBorderSize = 1.0f;
        style.WindowBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.ScrollbarSize = 12.0f;
        style.WindowPadding = ImVec2(10, 10);
        style.FramePadding = ImVec2(6, 4);
        style.ItemSpacing = ImVec2(8, 6);
        style.ItemInnerSpacing = ImVec2(6, 4);
        style.IndentSpacing = 22.0f;

        style.WindowMenuButtonPosition = ImGuiDir_Right;
        style.ColorButtonPosition = ImGuiDir_Right;

        // -- Cores: base #333 (cinza escurão) e destaques laranja-avermelhados --
        // Texto
        colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f); // Um branquinho suave
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

        // Fundo principal e popups
        colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); // ~#333
        colors[ImGuiCol_ChildBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);

        // Bordas
        colors[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.40f, 0.80f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        // Fundo de frames, com leve destaque no hover
        colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);

        // Título e Menubar
        colors[ImGuiCol_TitleBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.18f, 0.18f, 0.18f, 0.75f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

        // Scrollbars
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.30f, 0.30f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.60f, 0.35f, 0.35f, 1.00f);

        // Laranja avermelhado (quase vermelho)
        ImVec4 accentNormal = ImVec4(0.10f, 0.30f, 0.25f, 1.00f); // ~#FF4B3E
        ImVec4 accentHover = ImVec4(0.10f, 0.35f, 0.30f, 1.00f);
        ImVec4 accentActive = ImVec4(0.10f, 0.40f, 0.35f, 1.00f);

        colors[ImGuiCol_CheckMark] = accentNormal;
        colors[ImGuiCol_SliderGrab] = accentNormal;
        colors[ImGuiCol_SliderGrabActive] = accentActive;
        colors[ImGuiCol_Button] = accentNormal;
        colors[ImGuiCol_ButtonHovered] = accentHover;
        colors[ImGuiCol_ButtonActive] = accentActive;
        colors[ImGuiCol_Header] = accentNormal;
        colors[ImGuiCol_HeaderHovered] = accentHover;
        colors[ImGuiCol_HeaderActive] = accentActive;
        colors[ImGuiCol_Separator] = accentNormal;
        colors[ImGuiCol_SeparatorHovered] = accentHover;
        colors[ImGuiCol_SeparatorActive] = accentActive;
        colors[ImGuiCol_ResizeGrip] = accentNormal;
        colors[ImGuiCol_ResizeGripHovered] = accentHover;
        colors[ImGuiCol_ResizeGripActive] = accentActive;
        colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_TabHovered] = accentHover;
        colors[ImGuiCol_TabActive] = accentActive;
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 0.30f, 0.25f, 0.70f);
        colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

        // Gráficos e seleções
        colors[ImGuiCol_PlotLines] = accentNormal;
        colors[ImGuiCol_PlotLinesHovered] = accentHover;
        colors[ImGuiCol_PlotHistogram] = accentNormal;
        colors[ImGuiCol_PlotHistogramHovered] = accentHover;
        colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.30f, 0.25f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.35f, 0.30f, 0.90f);
        colors[ImGuiCol_NavHighlight] = accentNormal;
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    }
}
