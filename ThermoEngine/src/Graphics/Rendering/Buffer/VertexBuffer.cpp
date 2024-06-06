#include "ThermoPch.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

namespace Thermo
{
    VertexBuffer::VertexBuffer(uint32_t size, void *data)
    {
        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(uint32_t size)
    {
        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    void VertexBuffer::SubData(uint32_t size, void *data) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Ref <VertexBuffer> VertexBuffer::Create(uint32_t size, void *data)
    {
        return CreateRef<VertexBuffer>(size, data);
    }

    Ref <VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        return CreateRef<VertexBuffer>(size);
    }
} // Thermo