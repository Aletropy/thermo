#include "Project.h"

#include <filesystem>
#include <fstream>
#include <utility>

#include <yaml-cpp/yaml.h>

#include "PathHelper.h"

namespace ThermoEditor
{
    Project Project::Instance = Project({});

    Project::Project(ProjectProperties projectProperties)
        : m_Props(std::move(projectProperties))
    {
    }

    YAML::Node Project::Serialize() const
    {
        auto node = YAML::Node();
        node["Name"] = m_Props.Name;
        node["VersionMajor"] = m_Props.VersionMajor;
        node["VersionMinor"] = m_Props.VersionMinor;
        node["VersionPatch"] = m_Props.VersionPatch;
        node["Author"] = m_Props.Author;
        return node;
    }

    ProjectProperties Project::DeserializeProject(const std::string &filepath)
    {
        YAML::Node node = YAML::LoadFile(filepath)["Project"];
        ProjectProperties props;
        props.Name = node["Name"].as<std::string>();
        props.VersionMajor = node["VersionMajor"].as<int>();
        props.VersionMinor = node["VersionMinor"].as<int>();
        props.VersionPatch = node["VersionPatch"].as<int>();
        props.Author = node["Author"].as<std::string>();
        return props;
    }

    void Project::SaveProject() const
    {
        auto node = YAML::Node();
        node["Project"] = Serialize();

        const auto path = std::filesystem::path(PathHelper::GetCurrentRootPath() + "ProjectInfo.yaml");
        if (!exists(path.parent_path()))
            create_directories(path.parent_path());

        auto file = std::ofstream(path.string());
        if (file.is_open())
        {
            file << node;
            file.close();
        }
    }

    Project Project::LoadOrCreateProject(const std::string &filepath)
    {
        const auto path = std::filesystem::path(filepath + "/ProjectInfo.yaml");
        if (!exists(path))
            return CreateProject(filepath);

        const auto info = DeserializeProject(path);
        auto project = Project(info);
        return project;
    }


    Project Project::CreateProject(const std::string &filepath)
    {
        auto project = Project({
            "New Project",
            1, 0, 0,
            "Me!"
        });
        project.SaveProject();
        return project;
    }
} // ThermoEditor
