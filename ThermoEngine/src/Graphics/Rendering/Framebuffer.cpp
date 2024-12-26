#include "ThermoPch.h"
#include "Framebuffer.h"

#include <glad/glad.h>

namespace Thermo
{
    Framebuffer::Framebuffer(const int width, const int height)
    {
        Invalidate(width, height);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_Id);
    }

    void Framebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
    }

    void Framebuffer::Invalidate(const int width, const int height)
    {
        if (width == m_Width && height == m_Height)
            return;

        m_Width = width;
        m_Height = height;

        if(m_Id)
        {
            glDeleteFramebuffers(1, &m_Id);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glCreateFramebuffers(1, &m_Id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Id);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
        glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, width, height);

        glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8, width, height);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Ref<Framebuffer> Framebuffer::Create(int width, int height)
    {
        return CreateRef<Framebuffer>(width, height);
    }
} // Thermo