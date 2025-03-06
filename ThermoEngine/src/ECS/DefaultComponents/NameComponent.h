#ifndef NAMECOMPONENT_H
#define NAMECOMPONENT_H

#include <string>
#include <utility>

namespace Thermo
{
    struct NameComponent
    {
        explicit NameComponent(std::string name)
            : Name(std::move(name))
        {
        }

        std::string Name = std::string();
    };
}

#endif //NAMECOMPONENT_H
