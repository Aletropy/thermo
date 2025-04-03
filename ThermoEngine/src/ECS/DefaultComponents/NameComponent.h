#ifndef NAMECOMPONENT_H
#define NAMECOMPONENT_H

#include <string>
#include <utility>

#include "ECS/Serialization/IComponentSerializer.h"
#include "ECS/ComponentRegistry.h"

namespace Thermo
{
    class NameComponent
    {
    public:
        std::string Name = std::string();
    };

    DEFINE_COMPONENT_SERIALIZER(NameComponent,
                                {
                                node["Name"] = component->Name;
                                },
                                {
                                component.Name = node["Name"].as<std::string>();
                                }
    )
}


#endif //NAMECOMPONENT_H
