#include "ExplorerPanel.h"

#include <Thermo.h>

#include "imgui.h"

#include <string>
#include <cstdlib>

#include "PathHelper.h"
#include "Core/Base.h"
#ifdef _WIN32
#include <windows.h>
#endif

using namespace Thermo;

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
    static std::filesystem::path s_SelectedPath = std::filesystem::current_path();

    struct Icons
    {
        Ref<Texture2D> FolderIcon;
        Ref<Texture2D> FileIcon;
        Ref<Texture2D> ImageIcon;
    };

    static Icons s_Icons;

    void ExplorerPanel::Load(const std::filesystem::path &path)
    {
        s_CurrentPath = path;
        s_SelectedPath = path;
        LoadIcons();
    }

    void ExplorerPanel::LoadIcons()
    {
        s_Icons = Icons();

        s_Icons.FolderIcon = Texture2D::Create("assets/textures/icons/folder.png");
        s_Icons.FileIcon = Texture2D::Create("assets/textures/icons/file.png");
        s_Icons.ImageIcon = Texture2D::Create("assets/textures/icons/file_image.png");
    }

    uint32_t ExplorerPanel::GetIconTexture(const std::filesystem::path &path)
    {
        if (is_directory(path))
            return s_Icons.FolderIcon->GetId();

        const auto extension = path.extension();
        if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
            return s_Icons.ImageIcon->GetId();

        return s_Icons.FileIcon->GetId();
    }

    void ExplorerPanel::DisplayExplorerPanel()
    {
        const auto currentPath = s_CurrentPath;

        ImGui::Begin("Explorer");

        if (currentPath.has_parent_path() && currentPath.compare(currentPath.parent_path()))
        {
            if (ImGui::Button(".."))
            {
                s_CurrentPath = currentPath.parent_path();
                goto EndPanel;
            }
        }
        ImGui::SameLine();

        ImGui::Text("Current Path: %s", currentPath.c_str());

        for (const auto &entry: std::filesystem::directory_iterator(s_CurrentPath))
        {
            const auto &path = entry.path();
            const auto iconId = reinterpret_cast<void *>(GetIconTexture(path));

            ImGui::Image(iconId, ImVec2(16, 16), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::SameLine();

            if (ImGui::Selectable(path.filename().c_str(), !s_SelectedPath.compare(path),
                                  ImGuiSelectableFlags_AllowDoubleClick))
            {
                if (ImGui::IsMouseDoubleClicked(0))
                {
                    if (is_directory(path))
                    {
                        s_CurrentPath = path;
                        goto EndPanel;
                    }

                    OpenFileInDefaultApp(path);
                } else
                {
                    s_SelectedPath = path;
                }
            }

            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
            {
                std::string filePathStr = path.string();
                ImGui::SetDragDropPayload("IMAGE", filePathStr.c_str(), filePathStr.size() + 1);

                ImGui::Image(iconId, ImVec2(16, 16), ImVec2(0, 1), ImVec2(1, 0));
                ImGui::SameLine();
                ImGui::Text("%s", path.filename().string().c_str());

                ImGui::EndDragDropSource();
            }


            if (ImGui::BeginPopupContextItem(path.string().c_str()))
            {
                if (ImGui::MenuItem("Open"))
                {
                    if (is_directory(path))
                    {
                        s_CurrentPath = path;
                        ImGui::EndPopup();
                        goto EndPanel;
                    }
                    OpenFileInDefaultApp(path);
                }

                if (ImGui::MenuItem("Delete"))
                {
                    remove_all(path);
                }

                ImGui::EndPopup();
            }
        }

    EndPanel:
        ImGui::End();
    }

    std::filesystem::path ExplorerPanel::GetExplorerPath()
    {
        return s_CurrentPath;
    }
} // ThermoEditor
