#include "ThermoPch.h"
#include "Spritesheet.h"

namespace Thermo
{
    Spritesheet::Spritesheet(const std::string &filepath, const int spriteWidth, const int spriteHeight,
                             const int framesPerRow,
                             const int framesPerColumn)
    {
        m_Texture = Texture2D::Create(filepath);

        const auto texWidth = static_cast<float>(m_Texture->GetWidth());
        const auto texHeight = static_cast<float>(m_Texture->GetHeight());

        const int totalFrames = framesPerRow * framesPerColumn;

        m_SubTextures.reserve(totalFrames);

        for (int i = 0; i < totalFrames; i++)
        {
            // row e col pra descobrir onde tá o sprite na imagem
            int row = i / framesPerRow; // Linha
            int col = i % framesPerRow; // Coluna

            // Calcula o offset em pixels
            float xOffset = static_cast<float>(col * spriteWidth);
            float yOffset = static_cast<float>(row * spriteHeight);

            // Converte pra coordenadas [0..1]
            float u = xOffset / texWidth;
            float v = (texHeight - yOffset - spriteHeight) / texHeight;

            float uSize = static_cast<float>(spriteWidth) / texWidth;
            float vSize = static_cast<float>(spriteHeight) / texHeight;

            // Cria o SubTexture2D e bota na lista
            m_SubTextures.push_back({m_Texture, {u, v}, {uSize, vSize}});
        }
    }

    SubTexture2D Spritesheet::GetFrame(const int index)
    {
        return m_SubTextures[index];
    }

    SubTexture2D Spritesheet::GetFrame(const int x, const int y)
    {
        return m_SubTextures[y * m_Texture->GetWidth() + x];
    }
} // Thermo
