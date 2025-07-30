#include "ProjectPanel.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "Core/Project.h"

#include <Thermo.h>

namespace ThermoEditor
{
    void ProjectPanel::RenderProjectPanel()
    {
        ImGui::Begin("Project");
        auto &[Name, VersionMajor, VersionMinor, VersionPatch, Author] = Project::Instance.GetProjectProperties();

        ImGui::Text("Properties");
        ImGui::Separator();

        if (ImGui::InputText("Name", &Name))
        {
            Thermo::Application::Instance->ChangeWindowName(
                "Thermo Editor | " + Name);
        }
        ImGui::InputText("Author", &Author);
        ImGui::Text("Version");
        ImGui::Separator();
        ImGui::InputInt("Major", &VersionMajor);
        ImGui::InputInt("Minor", &VersionMinor);
        ImGui::InputInt("Patch", &VersionPatch);
        ImGui::End();
    }
} // ThermoEditor
