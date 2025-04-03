#ifndef PROJECTINFO_H
#define PROJECTINFO_H
#include <string>

namespace ThermoEditor
{
    struct ProjectProperties
    {
        std::string Name;
        int VersionMajor;
        int VersionMinor;
        int VersionPatch;
        std::string Author;
    };
}

#endif //PROJECTINFO_H
