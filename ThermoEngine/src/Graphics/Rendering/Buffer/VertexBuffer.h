#ifndef THERMOENGINE_VERTEXBUFFER_H
#define THERMOENGINE_VERTEXBUFFER_H

namespace Thermo
{
    class VertexBuffer
    {
    public:
        VertexBuffer(uint32_t size, void* data);
        explicit VertexBuffer(uint32_t size);

        void SubData(uint32_t size, void* data) const;

        void Bind() const;
        static void Unbind();

    private:
        uint32_t m_Id{};
    };

    struct VertexElement
    {
        uint32_t Offset;
        uint32_t Count;
        uint32_t Type;
        uint32_t Normalized;
    };

    class VertexLayout
    {
    public:
        void PushFloat(uint32_t count)
        {
            const uint32_t type = 0x1406;
            m_Elements.push_back({m_Stride, count, type, false});
            m_Stride += count * sizeof(float);
        }

        [[nodiscard]] inline uint32_t Stride() const { return m_Stride; }
        [[nodiscard]] inline const std::vector<VertexElement>& Elements() const { return m_Elements; }

    private:
        uint32_t m_Stride = 0;
        std::vector<VertexElement> m_Elements;
    };

} // Thermo

#endif //THERMOENGINE_VERTEXBUFFER_H
