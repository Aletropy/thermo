#ifndef ICOMPONENTSERIALIZER_H
#define ICOMPONENTSERIALIZER_H

#include "ECS/EntityManager.h"
#include "yaml-cpp/yaml.h"

#define DEFINE_COMPONENT_SERIALIZER(ComponentType, SER_BODY, DESER_BODY) \
template<> inline YAML::Node ComponentSerializer<ComponentType>::Serialize(void* componentData) { \
    YAML::Node node; \
    auto* component = static_cast<ComponentType*>(componentData); \
    SER_BODY \
    YAML::Node compNode; \
    compNode[#ComponentType] = node; \
    compNode["TypeId"] = typeid(ComponentType).hash_code();    \
    return compNode; \
} \
template<> inline void ComponentSerializer<ComponentType>::Deserialize(const Ref<EntityManager>& em, const EntityId entityId, const YAML::Node& compNode) { \
    em->AddComponent<ComponentType>(entityId); \
    auto& component = em->GetComponent<ComponentType>(entityId); \
    auto node = compNode[#ComponentType]; \
    DESER_BODY \
} \
template<> inline const char* ComponentSerializer<ComponentType>::GetComponentName() { \
    return #ComponentType; \
} \
template<> inline void ComponentSerializer<ComponentType>::CreateNew(const Ref<EntityManager>& em, const EntityId entityId) { \
    auto component = em->GetRegistry().try_get<ComponentType>(static_cast<entt::entity>(entityId)); \
    if(component == nullptr) \
        em->AddComponent<ComponentType>(entityId); \
}


namespace Thermo
{
    class IComponentSerializer
    {
    public:
        virtual ~IComponentSerializer() = default;

        virtual YAML::Node Serialize(void *data) = 0;

        virtual void Deserialize(const Ref<EntityManager> &em, EntityId entityId, const YAML::Node &node) = 0;

        virtual void CreateNew(const Ref<EntityManager> &em, EntityId entityId) = 0;

        virtual const char *GetComponentName() = 0;
    };

    template<typename T>
    class ComponentSerializer final : public IComponentSerializer
    {
    public:
        YAML::Node Serialize(void *componentData) override
        {
            THERMO_ERROR("Component serialization not implemented.", 0);
            return {};
        }

        void Deserialize(const Ref<EntityManager> &em, EntityId entityId, const YAML::Node &node) override
        {
            THERMO_ERROR("Component serialization not implemented.", 0);
        }

        const char *GetComponentName() override { return ""; }

        void CreateNew(const Ref<EntityManager> &em, EntityId entityId) override
        {
        }
    };
}

#endif //ICOMPONENTSERIALIZER_H
