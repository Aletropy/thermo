#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "glm/vec4.hpp"
#include "Graphics/Colors.h"
#include "Graphics/Rendering/Texture/Texture2D.h"

namespace Thermo
{
    class QuadRendererComponent
    {
    public:
        Ref<Texture2D> Texture = nullptr;
        glm::vec4 Color = Colors::WHITE;
    };

    DEFINE_COMPONENT_SERIALIZER(QuadRendererComponent,
                                {
                                node["Color"]["R"] = component->Color.r;
                                node["Color"]["G"] = component->Color.g;
                                node["Color"]["B"] = component->Color.b;
                                node["Color"]["A"] = component->Color.a;
                                node["TexturePath"] = component->Texture != nullptr ?
                                component->Texture->GetFilepath() : std::string();
                                },
                                {
                                component.Color = glm::vec4(
                                    node["Color"]["R"].as<float>(),
                                    node["Color"]["G"].as<float>(),
                                    node["Color"]["B"].as<float>(),
                                    node["Color"]["A"].as<float>()
                                );
                                const auto texturePath = node["TexturePath"].as<std::string>();
                                component.Texture = texturePath.empty() ? nullptr : Texture2D::Create(texturePath);
                                }
    )

    REGISTER_COMPONENT(QuadRendererComponent,
                       COMPONENT_PROPERTY(QuadRendererComponent, Texture, PropertyType::TexturePtr)
                       COMPONENT_PROPERTY(QuadRendererComponent, Color, PropertyType::Color)
    )
}

#endif //QUADRENDERER_H
