#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include "ECS/ComponentRegistry.h"
#include "ECS/Serialization/IComponentSerializer.h"

namespace Thermo
{
    enum class CameraType : int
    {
        Orthographic,
        Perspective
    };

    class CameraComponent
    {
    public:
        CameraType Type = CameraType::Orthographic;
        float Zoom = 5.0f;
    };

    DEFINE_COMPONENT_SERIALIZER(CameraComponent,
                                {
                                node["Type"] = static_cast<int>(component->Type);
                                node["Zoom"] = component->Zoom;
                                },
                                {
                                component.Type = static_cast<CameraType>(node["Type"].as<int>());
                                component.Zoom = node["Zoom"].as<float>();
                                }
    )

    REGISTER_COMPONENT(CameraComponent,
                       COMPONENT_PROPERTY(CameraComponent, Zoom, PropertyType::Float)
    )
}

#endif //CAMERACOMPONENT_H
