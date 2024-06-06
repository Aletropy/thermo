#include "ThermoPch.h"
#include "Batch2D.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"

#include "Renderer.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Thermo
{

    static const glm::vec4 VertexPositions[4] = {
            { -1.0f, -1.0f, 0.0f, 1.0f },
            { -1.0f, 1.0f, 0.0f, 1.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f },
            { 1.0f, -1.0f, 0.0f, 1.0f }
    };

    struct QuadVertex
    {
        glm::vec4 Position;
        glm::vec4 Color;
    };

    struct BatchData
    {
        static const uint32_t MaxQuads = 1000;
        static const uint32_t MaxVertices = MaxQuads * 4;
        static const uint32_t MaxIndices = MaxQuads * 6;

        QuadVertex* QuadVertexBufferBase;
        QuadVertex* QuadVertexBufferPtr;

        Ref<VertexBuffer> VertexBuffer;
        Ref<IndexBuffer> IndexBuffer;
        Ref<VertexArray> VertexArray;

        Ref<Shader> Shader;

        uint32_t IndicesCount;
    };

    static BatchData s_Data{};
    void Batch2D::Initialize()
    {
        s_Data.QuadVertexBufferBase = new QuadVertex[BatchData::MaxVertices];
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.VertexArray = VertexArray::Create();
        s_Data.VertexBuffer = VertexBuffer::Create(BatchData::MaxVertices * sizeof(QuadVertex));

        VertexLayout layout;

        layout.PushFloat(4);
        layout.PushFloat(4);

        s_Data.VertexArray->AddVertexBuffer(s_Data.VertexBuffer, layout);

        auto* indices = new uint32_t[BatchData::MaxIndices];
        uint32_t offset = 0;

        for(uint32_t i = 0; i < BatchData::MaxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        s_Data.IndexBuffer = IndexBuffer::Create(BatchData::MaxIndices * sizeof(uint32_t), indices);
        delete[] indices;

        s_Data.VertexArray->SetIndexBuffer(s_Data.IndexBuffer);

        s_Data.Shader = Shader::Create("assets/defaultShader.vert", "assets/defaultShader.frag");
    }

    void Batch2D::PushQuad(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(
                glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));

        if(s_Data.IndicesCount >= BatchData::MaxIndices)
            NextBatch();

        for(auto VertexPosition : VertexPositions)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * VertexPosition;
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.IndicesCount += 6;
    }

    void Batch2D::BeginBatch()
    {
        NextBatch();
    }

    void Batch2D::EndBatch()
    {
        Flush();
    }

    void Batch2D::Shutdown()
    {
        Flush();
    }

    void Batch2D::NextBatch()
    {
        s_Data.IndicesCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Batch2D::Flush()
    {
        uint32_t size = uint8_t((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);

        s_Data.VertexBuffer->SubData(size, s_Data.QuadVertexBufferBase);

        s_Data.Shader->Bind();

        Renderer::DrawIndexed(s_Data.VertexArray, s_Data.IndicesCount);
    }
} // Thermo