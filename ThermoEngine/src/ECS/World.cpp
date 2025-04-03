#include "World.h"

#include <filesystem>
#include <utility>
#include <yaml-cpp/node/node.h>

#include "Serialization/SerializeTools.h"

namespace Thermo
{
    World::World(std::string debugName)
        : m_DebugName(std::move(debugName))
    {
        m_SystemManager = CreateRef<SystemManager>();
        m_EntityManager = CreateRef<EntityManager>();
    }

    void World::Initialize() const
    {
        m_SystemManager->InitializeSystems();
        THERMO_LOG("World %s initialized!", m_DebugName.c_str());
    }

    void World::Update(const float deltaTime) const
    {
        m_SystemManager->UpdateSystems(deltaTime);
    }

    void World::SaveToFile(const std::string &worldsPath) const
    {
        const YAML::Node node = SerializeTools::SerializeWorld(*this);
        auto filePath = std::filesystem::path(worldsPath + m_DebugName + ".world");

        if (!exists(filePath.parent_path()))
            create_directories(filePath.parent_path());

        std::ofstream file(filePath);
        if (file.is_open())
        {
            file << node;
            file.close();
            THERMO_LOG("World saved to %s successfully", filePath.c_str());
        } else
        {
            THERMO_ERROR("Failed to save to file! Path: %s", filePath.c_str());
        }
    }

    Ref<World> World::LoadOrCreate(const std::string &filePath)
    {
        const auto finalPath = std::filesystem::path(filePath);
        if (exists(finalPath))
            return LoadFromFile(finalPath);
        return CreateRef<World>("New World");
    }

    Ref<World> World::LoadFromFile(const std::string &filePath)
    {
        const YAML::Node root = YAML::LoadFile(filePath);
        THERMO_LOG("Loading world from %s", filePath.c_str());
        return SerializeTools::DeserializeWorld(root);
    }
} // Thermo
