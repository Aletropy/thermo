#ifndef THERMOENGINE_SPARSESET_H
#define THERMOENGINE_SPARSESET_H
#include <cstdint>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Thermo
{
    template<typename T>
    class SparseSet
    {
    public:
        void Add(const uint32_t id, const T &t)
        {
            if (!m_IdToIndex.contains(id))
            {
                const uint32_t index = m_Data.size();
                m_IdToIndex[id] = index;
                m_IndexToId[index] = id;
                m_Data.push_back(t);
            }
        }

        void Remove(const uint32_t id)
        {
            if (const auto it = m_IdToIndex.find(id); it != m_IdToIndex.end())
            {
                uint32_t index = it->second;
                uint32_t last = m_Data.size() - 1;

                std::swap(m_Data[index], m_Data[last]);
                std::swap(m_IndexToId[index], m_IndexToId[last]);

                m_IdToIndex[m_IndexToId[index]] = index;

                m_Data.pop_back();
                m_IdToIndex.erase(it);
                m_IndexToId.erase(last);
            }
        }

        T &Get(uint32_t id)
        {
            return m_Data[m_IdToIndex[id]];
        }

        bool Has(const uint32_t id) const
        {
            return m_IdToIndex.contains(id);
        }

        const std::pmr::vector<T> &GetData() const
        {
            return m_Data;
        }

    private:
        std::vector<T> m_Data;
        std::pmr::unordered_map<uint32_t, uint32_t> m_IdToIndex;
        std::unordered_map<uint32_t, uint32_t> m_IndexToId;
    };
} // Thermo

#endif //THERMOENGINE_SPARSESET_H
