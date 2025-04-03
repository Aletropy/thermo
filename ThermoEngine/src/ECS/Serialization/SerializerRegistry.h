#ifndef SERIALIZERREGISTRY_H
#define SERIALIZERREGISTRY_H
#include "IComponentSerializer.h"


namespace Thermo
{
    using Registry = std::unordered_map<std::size_t, std::unique_ptr<IComponentSerializer> >;

    class SerializerRegistry
    {
    public:
        template<typename T>
        static void RegisterComponentSerializer(const size_t typeId)
        {
            m_Registry[typeId] = std::make_unique<ComponentSerializer<T> >();
        }

        static const Registry &GetRegistry() { return m_Registry; }

    private:
        static Registry m_Registry;
    };
} // Thermo

#endif //SERIALIZERREGISTRY_H
