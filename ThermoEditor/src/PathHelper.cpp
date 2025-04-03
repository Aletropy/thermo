#include "PathHelper.h"

namespace ThermoEditor
{
    std::filesystem::path PathHelper::s_CurrentPath = std::filesystem::current_path();

    void PathHelper::StartAtPath(const std::filesystem::path &path)
    {
        if (path.string().ends_with("/"))
            s_CurrentPath = path;
        else
            s_CurrentPath = s_CurrentPath.append("/");

        s_CurrentPath = path;

        if (!exists(s_CurrentPath))
            create_directories(s_CurrentPath);
    }

    std::string PathHelper::GetCurrentRootPath()
    {
        return s_CurrentPath.string();
    }

    std::string PathHelper::GetWorldPath(const std::string &worldName)
    {
        return GetCurrentWorldsPath() + worldName + ".world";
    }

    std::string PathHelper::GetCurrentWorldsPath()
    {
        return s_CurrentPath.string() + "Worlds/";
    }
} // ThermoEditor
