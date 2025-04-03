#ifndef SERIALIZETOOLS_H
#define SERIALIZETOOLS_H
#include <yaml-cpp/node/node.h>

#include "SerializerRegistry.h"
#include "ECS/World.h"
#include "glm/vec3.hpp"

namespace Thermo
{
    class SerializeTools
    {
    public:
        static YAML::Node SerializeWorld(const World &world)
        {
            YAML::Node node;
            node["World"]["DebugName"] = world.GetDebugName();

            const auto &em = world.GetEntityManager();

            YAML::Node entitiesNode;
            for (const auto entity: em->GetEntities())
                entitiesNode.push_back(SerializeEntity(em, entity));

            node["World"]["Entities"] = entitiesNode;
            return node;
        }

        static Ref<World> DeserializeWorld(const YAML::Node &node)
        {
            auto worldNode = node["World"];

            auto world = CreateRef<World>(worldNode["DebugName"].as<std::string>());

            for (const auto entityNode: worldNode["Entities"])
            {
                const auto &em = world->GetEntityManager();
                const auto entity = em->CreateEntity();

                for (const auto componentNode: entityNode["Components"])
                {
                    auto typeId = componentNode["TypeId"].as<size_t>();
                    auto it = SerializerRegistry::GetRegistry().find(typeId);
                    if (it == SerializerRegistry::GetRegistry().end())
                        continue;

                    it->second->Deserialize(em, entity, componentNode);
                }
            }

            return world;
        }

        static YAML::Node SerializeEntity(const Ref<EntityManager> &entityManager, const EntityId entityId)
        {
            YAML::Node node;
            node["Id"] = entityId;

            YAML::Node compsNode;
            for (const auto &second: entityManager->GetAllComponents(entityId) | std::views::values)
            {
                compsNode.push_back(SerializeComponent(second));
            }

            node["Components"] = compsNode;

            return node;
        }

        static YAML::Node SerializeComponent(const ComponentWrapper &wrapper)
        {
            const auto &registry = SerializerRegistry::GetRegistry();
            const auto it = registry.find(wrapper.typeId);
            if (it == registry.end())
                return {};

            const auto &serializer = it->second;

            return serializer->Serialize(wrapper.data);
        }
    };
}

inline void SerializeVector3(const std::string &name, const glm::vec3 &value, YAML::Node &node)
{
    node[name]["x"] = value.x;
    node[name]["y"] = value.y;
    node[name]["z"] = value.z;
}

inline glm::vec3 DeserializeVector3(const std::string &name, const YAML::Node &node)
{
    return {
        node[name]["x"].as<float>(),
        node[name]["y"].as<float>(),
        node[name]["z"].as<float>()
    };
}

#endif //SERIALIZETOOLS_H
