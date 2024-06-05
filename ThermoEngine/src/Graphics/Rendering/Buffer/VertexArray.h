#ifndef THERMOENGINE_VERTEXARRAY_H
#define THERMOENGINE_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Thermo
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        static void Unbind() ;

        void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer, const VertexLayout& layout) const;
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) const;
    private:
        uint32_t m_Id{};
    };
}


#endif //THERMOENGINE_VERTEXARRAY_H
