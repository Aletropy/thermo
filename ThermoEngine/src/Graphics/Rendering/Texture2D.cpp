#include "ThermoPch.h"
#include "Texture2D.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Thermo
{
    Texture2D::Texture2D(const std::string &filepath)
    {
        stbi_set_flip_vertically_on_load(true);

        int w, h, c;
        stbi_uc* data = stbi_load(filepath.c_str(), &w, &h, &c, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
        glTextureStorage2D(m_Id, 1, GL_RGBA8, w, h);

        glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_Id, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_Id);
    }

    void Texture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_Id);
    }

    Ref<Texture2D> Texture2D::Create(const std::string &filepath)
    {
        return CreateRef<Texture2D>(filepath);
    }
} // Thermo