#include "ThermoPch.h"
#include "IndexBuffer.h"
#include "glad/glad.h"

namespace Thermo
{
    IndexBuffer::IndexBuffer(uint32_t size, void *data)
    {
        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    IndexBuffer::IndexBuffer(uint32_t size)
    {
        glCreateBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    void IndexBuffer::SubData(uint32_t size, void *data) const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    Ref <IndexBuffer> IndexBuffer::Create(uint32_t size, void *data)
    {
        return CreateRef<IndexBuffer>(size, data);
    }

    Ref <IndexBuffer> IndexBuffer::Create(uint32_t size)
    {
        return CreateRef<IndexBuffer>(size);
    }
} // Thermo