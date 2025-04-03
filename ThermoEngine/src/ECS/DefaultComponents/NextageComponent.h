#ifndef NEXTAGECOMPONENT_H
#define NEXTAGECOMPONENT_H

#include "Core/Base.h"
#include "ECS/ComponentRegistry.h"
#include "ECS/Serialization/IComponentSerializer.h"

namespace Thermo
{
    class NextageComponent
    {
    public:
        float NextageLevel = 0.0f;
    };

    DEFINE_COMPONENT_SERIALIZER(NextageComponent,
                                {
                                node["NextageLevel"] = component->NextageLevel;
                                },
                                {
                                component.NextageLevel = node["NextageLevel"].as<float>();
                                });

    REGISTER_COMPONENT(NextageComponent,
                       COMPONENT_PROPERTY(NextageComponent, NextageLevel, PropertyType::Float)
    )
}

#endif //NEXTAGECOMPONENT_H
