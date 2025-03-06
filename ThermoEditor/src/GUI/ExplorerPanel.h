
#ifndef EXPLORERPANEL_H
#define EXPLORERPANEL_H
#include <filesystem>

namespace ThermoEditor
{
    class ExplorerPanel
    {
    public:
        static void DisplayExplorerPanel();

        static std::filesystem::path GetExplorerPath();
    };
} // ThermoEditor

#endif //EXPLORERPANEL_H
