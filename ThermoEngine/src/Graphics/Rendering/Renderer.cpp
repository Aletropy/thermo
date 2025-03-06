#include "ThermoPch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Thermo
{
    void Renderer::Initialize()
    {
        THERMO_ASSERT(gladLoadGL(), "%s", "Failed to initialize glad.");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);

        const auto glVersion = glGetString(GL_VERSION);

        THERMO_LOG("Renderer Initialized: %s", glVersion);

        // glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
    }

    void Renderer::SetClearColor(const glm::vec4 &color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Terminate()
    {
        // TODO Finalize renderer objects
    }

    void Renderer::DrawIndexed(const Ref<VertexArray> &vertexArray, const uint32_t indexCount)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
    {
        glViewport(
            static_cast<GLint>(x),
            static_cast<GLint>(y),
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height));
    }
} // Thermo
