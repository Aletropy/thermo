#include "ThermoPch.h"
#include "VertexArray.h"

#include <glad/glad.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"

namespace Thermo
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_Id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_Id);
    }

    void VertexArray::SetIndexBuffer(const Ref <IndexBuffer> &indexBuffer) const
    {
        glBindVertexArray(m_Id);
        indexBuffer->Bind();
    }

    void VertexArray::AddVertexBuffer(const Ref <VertexBuffer> &vertexBuffer, const VertexLayout &layout) const
    {
        glBindVertexArray(m_Id);
        vertexBuffer->Bind();

        auto& elements = layout.Elements();

        for (int i = 0; i < elements.size(); ++i)
        {
            auto& element = elements[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, (GLint)element.Count, element.Type, element.Normalized, (GLsizei)layout.Stride(), (const void*)element.Offset);
        }
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_Id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    Ref<VertexArray> VertexArray::Create()
    {
        return CreateRef<VertexArray>();
    }
}
#pragma clang diagnostic pop