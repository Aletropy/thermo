
#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include "SubTexture2D.h"
#include "Texture2D.h"

namespace Thermo
{
    class Spritesheet
    {
    public:
        Spritesheet(
            const std::string &filepath,
            int spriteWidth, int spriteHeight,
            int framesPerRow, int framesPerColumn
        );

        SubTexture2D GetFrame(int index);

        SubTexture2D GetFrame(int x, int y);

    private:
        Ref<Texture2D> m_Texture;
        std::vector<SubTexture2D> m_SubTextures;
    };
} // Thermo

#endif //SPRITESHEET_H
