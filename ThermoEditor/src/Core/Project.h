
#ifndef PROJECT_H
#define PROJECT_H
#include <yaml-cpp/node/convert.h>

#include "ProjectProperties.h"

namespace ThermoEditor
{
    class Project
    {
    public:
        static Project Instance;

    public:
        static Project LoadOrCreateProject(const std::string &filepath);

        static ProjectProperties DeserializeProject(const std::string &filepath);

        explicit Project(ProjectProperties projectProperties);

        [[nodiscard]] YAML::Node Serialize() const;

        void SaveProject() const;

        [[nodiscard]] ProjectProperties &GetProjectProperties() { return m_Props; }
        [[nodiscard]] const ProjectProperties &GetProjectProperties() const { return m_Props; }

        [[nodiscard]] std::string GetProjectName() const { return m_Props.Name; }
        [[nodiscard]] std::string GetProjectAuthor() const { return m_Props.Author; }

        [[nodiscard]] std::string GetProjectVersion() const
        {
            return std::to_string(m_Props.VersionMajor) + "." +
                   std::to_string(m_Props.VersionMinor) + "." +
                   std::to_string(m_Props.VersionPatch);
        }

    private:
        static Project CreateProject(const std::string &filepath);

        ProjectProperties m_Props{};
    };
} // ThermoEditor

#endif //PROJECT_H
