#ifndef THERMOENGINE_INDEXBUFFER_H
#define THERMOENGINE_INDEXBUFFER_H

namespace Thermo
{
    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t size, void* data);
        explicit IndexBuffer(uint32_t size);

        void SubData(uint32_t size, void* data) const;

        void Bind() const;
        static void Unbind();

    private:
        uint32_t m_Id{};
    };

} // Thermo

#endif //THERMOENGINE_INDEXBUFFER_H
