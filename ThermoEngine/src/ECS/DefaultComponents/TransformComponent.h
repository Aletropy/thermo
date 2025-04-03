#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <yaml-cpp/node/node.h>

#include "ECS/ComponentRegistry.h"
#include "ECS/Serialization/IComponentSerializer.h"
#include "ECS/Serialization/SerializeTools.h"
#include "glm/vec3.hpp"

namespace Thermo
{
    class TransformComponent
    {
    public:
        glm::vec3 Position = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);
        glm::vec3 Rotation = glm::vec3(0.0f);
    };

    DEFINE_COMPONENT_SERIALIZER(TransformComponent,
                                {
                                SerializeVector3("Position", component->Position, node);
                                SerializeVector3("Scale", component->Scale, node);
                                SerializeVector3("Rotation", component->Rotation, node);
                                },
                                {
                                component.Position = DeserializeVector3("Position", node);
                                component.Scale = DeserializeVector3("Scale", node);
                                component.Rotation = DeserializeVector3("Rotation", node);
                                }
    )

    REGISTER_COMPONENT(TransformComponent,
                       COMPONENT_PROPERTY(TransformComponent, Position, PropertyType::Vector3)
                       COMPONENT_PROPERTY(TransformComponent, Scale, PropertyType::Vector3)
                       COMPONENT_PROPERTY(TransformComponent, Rotation, PropertyType::Vector3))
}

#endif //TRANSFORM_H
