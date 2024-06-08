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

    static const glm::vec2 TextureCoords[4] = {
            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
            { 1.0f, 1.0f },
            { 1.0f, 0.0f }
    };

    struct QuadVertex
    {
        glm::vec4 Position;
        glm::vec4 Color;
    };

    struct CircleVertex
    {
        glm::vec4 Position;
        glm::vec2 TexCoords;
        float Radius;
        glm::vec4 Color;
    };

    struct BatchData
    {
        static const uint32_t MaxQuads = 1000;
        static const uint32_t MaxVertices = MaxQuads * 4;
        static const uint32_t MaxIndices = MaxQuads * 6;

        QuadVertex* QuadVertexBufferBase;
        QuadVertex* QuadVertexBufferPtr;

        CircleVertex* CircleVertexBufferBase;
        CircleVertex* CircleVertexBufferPtr;

        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<IndexBuffer> QuadIndexBuffer;
        Ref<VertexArray> QuadVertexArray;

        Ref<VertexBuffer> CircleVertexBuffer;
        Ref<IndexBuffer>  CircleIndexBuffer;
        Ref<VertexArray>  CircleVertexArray;

        Ref<Camera2D> Camera;

        Ref<Shader> QuadShader;
        Ref<Shader> CircleShader;

        uint32_t QuadIndicesCount;
        uint32_t CircleIndicesCount;
    };

    static BatchData s_Data{};
    void Batch2D::Initialize()
    {
        s_Data.QuadVertexBufferBase = new QuadVertex[BatchData::MaxVertices];
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.CircleVertexBufferBase = new CircleVertex[BatchData::MaxVertices];
        s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;

        s_Data.QuadVertexArray = VertexArray::Create();
        s_Data.CircleVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create((uint32_t)BatchData::MaxVertices * sizeof(QuadVertex));

        VertexLayout layout;

        layout.PushFloat(4);
        layout.PushFloat(4);

        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer, layout);

        s_Data.CircleVertexBuffer = VertexBuffer::Create(BatchData::MaxVertices * sizeof(CircleVertex));

        layout = VertexLayout();
        layout.PushFloat(4);
        layout.PushFloat(2);
        layout.PushFloat(1);
        layout.PushFloat(4);

        s_Data.CircleVertexArray->AddVertexBuffer(s_Data.CircleVertexBuffer, layout);

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

        s_Data.QuadIndexBuffer = IndexBuffer::Create(BatchData::MaxIndices * sizeof(uint32_t), indices);
        s_Data.CircleIndexBuffer = IndexBuffer::Create(BatchData::MaxIndices * sizeof(uint32_t), indices);
        delete[] indices;

        s_Data.QuadVertexArray->SetIndexBuffer(s_Data.QuadIndexBuffer);
        s_Data.CircleVertexArray->SetIndexBuffer(s_Data.CircleIndexBuffer);

        s_Data.QuadShader = Shader::Create("assets/defaultShader.vert", "assets/defaultShader.frag");
        s_Data.CircleShader = Shader::Create("assets/circleShader.vert", "assets/circleShader.frag");
    }

    void Batch2D::PushQuad(const glm::vec2 &position, const glm::vec2 &scale, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(
                glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));

        if(s_Data.QuadIndicesCount >= BatchData::MaxIndices)
            NextBatch();

        for(auto VertexPosition : VertexPositions)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * VertexPosition;
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndicesCount += 6;
    }

    void Batch2D::PushCircle(const glm::vec2 &position, float radius, const glm::vec2 &rotation, const glm::vec4 &color)
    {
        glm::mat4 transform = glm::translate(
                glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));


        if(s_Data.CircleIndicesCount >= BatchData::MaxIndices)
            NextBatch();

        for(int i = 0; i < 4; i++)
        {
            s_Data.CircleVertexBufferPtr->Position = transform * VertexPositions[i];
            s_Data.CircleVertexBufferPtr->TexCoords = TextureCoords[i];
            s_Data.CircleVertexBufferPtr->Radius = radius;
            s_Data.CircleVertexBufferPtr->Color = color;

            s_Data.CircleVertexBufferPtr++;
        }

        s_Data.CircleIndicesCount += 6;
    }

    void Batch2D::BeginBatch()
    {
        s_Data.QuadIndicesCount = 0;
        s_Data.CircleIndicesCount = 0;

        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
        s_Data.CircleVertexBufferPtr = s_Data.CircleVertexBufferBase;
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
        Flush();
        BeginBatch();
    }

    void Batch2D::Flush()
    {
        auto viewProjMatrix = glm::mat4(1.0f);

        if(s_Data.Camera)
        {
            viewProjMatrix = s_Data.Camera->GetViewProjMatrix();
        }

        auto size = uint32_t((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);

        if(size > 0)
        {
            s_Data.QuadVertexBuffer->SubData(size, s_Data.QuadVertexBufferBase);
            s_Data.QuadShader->Bind();

            s_Data.QuadShader->UploadMatrix4x4("u_ViewProjMatrix", glm::value_ptr(viewProjMatrix));

            Renderer::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndicesCount);
        }

        size = uint32_t((uint8_t*)s_Data.CircleVertexBufferPtr - (uint8_t*)s_Data.CircleVertexBufferBase);

        if(size > 0)
        {
            s_Data.CircleVertexBuffer->SubData(size, s_Data.CircleVertexBufferBase);
            s_Data.CircleShader->Bind();
            s_Data.CircleShader->UploadMatrix4x4("u_ViewProjMatrix", glm::value_ptr(viewProjMatrix));

            Renderer::DrawIndexed(s_Data.CircleVertexArray, s_Data.CircleIndicesCount);
        }
    }

    void Batch2D::SetCamera(const Ref <Camera2D> &camera)
    {
        s_Data.Camera = camera;
    }
} // Thermo