#ifndef COMPONENTREGISTRY_H
#define COMPONENTREGISTRY_H
#include <string>
#include <unordered_map>
#include <vector>

namespace Thermo
{
    enum class PropertyType
    {
        Undefined,
        Bool,
        Float,
        String,
        Integer,
        Pointer,
        Vector2,
        Vector3,
        Vector4,
        Color,
        TexturePtr
    };

    struct PropertyDescriptor
    {
        std::string name;
        PropertyType type;
        size_t offset;
    };

    struct ComponentDescriptor
    {
        std::string name;
        size_t size;
        std::vector<PropertyDescriptor> properties;
    };

    inline std::unordered_map<size_t, ComponentDescriptor> &GetComponentRegistry(
    )
    {
        static std::unordered_map<size_t, ComponentDescriptor> registry;
        return registry;
    }
}

#define REGISTER_COMPONENT(ComponentType, ...)                \
    namespace {                                               \
        struct ComponentType##Registrator {                   \
            ComponentType##Registrator() {                    \
                Thermo::ComponentDescriptor desc;             \
                desc.size = sizeof(ComponentType);            \
                desc.name = #ComponentType;                   \
                __VA_ARGS__                                   \
               Thermo::GetComponentRegistry()[typeid(ComponentType).hash_code()] = desc; \
            }                                                 \
        };                                                    \
static ComponentType##Registrator global_##ComponentType##Registrator; \
}

#define COMPONENT_PROPERTY(ComponentType, propName, propType)   \
    desc.properties.push_back({#propName, propType, offsetof(ComponentType, propName)});


#endif //COMPONENTREGISTRY_H
