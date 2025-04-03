
#ifndef EXPLORERPANEL_H
#define EXPLORERPANEL_H
#include <filesystem>

namespace ThermoEditor
{
    class ExplorerPanel
    {
    public:
        static void Load(const std::filesystem::path &path);

        static uint32_t GetIconTexture(const std::filesystem::path &path);

        static void DisplayExplorerPanel();

        static std::filesystem::path GetExplorerPath();

    private:
        static void LoadIcons();
    };
} // ThermoEditor

#endif //EXPLORERPANEL_H
