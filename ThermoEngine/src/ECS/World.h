#ifndef WORLD_H
#define WORLD_H
#include "EntityManager.h"
#include "SystemManager.h"
#include "glm/vec4.hpp"
#include "Graphics/Colors.h"

namespace Thermo
{
    struct WorldProperties
    {
        glm::vec4 SkyboxSolidColor = Colors::SKY_BLUE;
    };

    class World
    {
    public:
        explicit World(std::string debugName);

        void Initialize() const;

        void Update(float deltaTime) const;

        void SaveToFile(const std::string &worldsPath) const;

        [[nodiscard]] const Ref<EntityManager> &GetEntityManager() const { return m_EntityManager; }
        [[nodiscard]] const std::string &GetDebugName() const { return m_DebugName; }
        WorldProperties &GetProperties() { return m_Properties; }

        static Ref<World> LoadOrCreate(const std::string &filePath);

        static Ref<World> LoadFromFile(const std::string &filePath);

    private:
        std::string m_DebugName;
        WorldProperties m_Properties{};
        Ref<EntityManager> m_EntityManager;
        Ref<SystemManager> m_SystemManager;
    };
} // Thermo

#endif //WORLD_H
