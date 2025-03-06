
#ifndef INPUT_H
#define INPUT_H
#include "Keys.h"
#include "glm/vec2.hpp"

namespace Thermo
{
    class Input
    {
    public:
        static bool IsKeyPressed(Keys key);

        static bool IsMouseButtonPressed(Keys button);

        static glm::vec2 GetMousePosition();
    };
} // Thermo

#endif //INPUT_H
