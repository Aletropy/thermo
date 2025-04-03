
#ifndef PATHHELPER_H
#define PATHHELPER_H
#include <filesystem>

namespace ThermoEditor
{
    class PathHelper
    {
    private:
        static std::filesystem::path s_CurrentPath;

    public:
        static void StartAtPath(const std::filesystem::path &path);

        static std::string GetCurrentRootPath();

        static std::string GetWorldPath(const std::string &worldName);

        static std::string GetCurrentWorldsPath();
    };
} // ThermoEditor

#endif //PATHHELPER_H
