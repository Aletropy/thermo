#include "ExplorerPanel.h"

#include "imgui.h"

#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

namespace ThermoEditor
{
    bool OpenFileInDefaultApp(const std::string &path)
    {
#ifdef _WIN32
        HINSTANCE result = ShellExecuteA(
            nullptr,           // hWnd
            "open",            // lpOperation
            path.c_str(),      // lpFile
            nullptr,           // lpParameters
            nullptr,           // lpDirectory
            SW_SHOWNORMAL      // nShowCmd
        );
        return reinterpret_cast<intptr_t>(result) > 32;
#else
        const std::string cmd = std::string("xdg-open \"") + path + "\"";
        const int ret = std::system(cmd.c_str());
        return (ret == 0);
#endif
    }

    static std::filesystem::path s_CurrentPath = std::filesystem::current_path();

    void ExplorerPanel::DisplayExplorerPanel()
    {
        ImGui::Begin("Explorer");

        ImGui::Text("Current path: %s", s_CurrentPath.c_str());

        if (s_CurrentPath.has_parent_path())
        {
            if (ImGui::Button(".."))
                s_CurrentPath = s_CurrentPath.parent_path();
        }

        for (auto &entry: std::filesystem::directory_iterator(s_CurrentPath))
        {
            const auto &path = entry.path();
            auto name = path.filename().string();
            bool isDirectory = entry.is_directory();

            if (ImGui::Selectable((name + (isDirectory ? "/" : "")).c_str(), isDirectory,
                                  ImGuiSelectableFlags_AllowDoubleClick))
            {
                if (ImGui::IsMouseDoubleClicked(0))
                {
                    if (isDirectory)
                        s_CurrentPath = path;
                    else
                        OpenFileInDefaultApp(path);
                }
            }
        }

        if (ImGui::BeginPopupContextWindow("ExplorerContextMenu", ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Open in Explorer"))
                OpenFileInDefaultApp(s_CurrentPath);
            ImGui::EndPopup();
        }
        ImGui::End();
    }

    std::filesystem::path ExplorerPanel::GetExplorerPath()
    {
        return s_CurrentPath;
    }
} // ThermoEditor
