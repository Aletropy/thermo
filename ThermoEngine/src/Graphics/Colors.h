#ifndef THERMOENGINE_COLORS_H
#define THERMOENGINE_COLORS_H

#include "Core/Base.h"
#include <glm/glm.hpp>

namespace Thermo
{
    struct Colors
    {
        constexpr static const glm::vec4 WHITE = { 0.95f, 0.95f, 0.95f, 1.f };
        constexpr static const glm::vec4 BLACK = { 0.1f, 0.1f, 0.1f, 1.f };
        constexpr static const glm::vec4 RED = { 0.91f, 0.3f, 0.24f, 1.f };
        constexpr static const glm::vec4 GREEN = { 0.56f, 0.76f, 0.34f, 1.f };
        constexpr static const glm::vec4 BLUE = { 0.36f, 0.54f, 0.97f, 1.f };
        constexpr static const glm::vec4 YELLOW = { 1.f, 0.89f, 0.42f, 1.f };
        constexpr static const glm::vec4 MAGENTA = { 0.96f, 0.52f, 0.9f, 1.f };
        constexpr static const glm::vec4 CYAN = { 0.4f, 0.8f, 0.92f, 1.f };
        constexpr static const glm::vec4 ORANGE = { 1.f, 0.62f, 0.22f, 1.f };
        constexpr static const glm::vec4 PURPLE = { 0.72f, 0.52f, 0.98f, 1.f };
        constexpr static const glm::vec4 PINK = { 1.f, 0.71f, 0.76f, 1.f };
        constexpr static const glm::vec4 LIME = { 0.68f, 1.f, 0.44f, 1.f };
        constexpr static const glm::vec4 TEAL = { 0.36f, 0.64f, 0.64f, 1.f };
        constexpr static const glm::vec4 SKY_BLUE = { 0.53f, 0.81f, 0.92f, 1.f };
        constexpr static const glm::vec4 NICE_DARK_BLUE = { 0.08f, 0.40f, 0.8f, 1.f };
        constexpr static const glm::vec4 LAVENDER = { 0.87f, 0.63f, 1.f, 1.f };
        constexpr static const glm::vec4 BROWN = { 0.71f, 0.49f, 0.35f, 1.f };
        constexpr static const glm::vec4 TURQUOISE = { 0.4f, 0.82f, 0.72f, 1.f };
    };
}

#endif //THERMOENGINE_COLORS_H
