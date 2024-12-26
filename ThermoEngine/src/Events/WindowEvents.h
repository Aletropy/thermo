#ifndef THERMO_WINDOW_EVENTS_H
#define THERMO_WINDOW_EVENTS_H

#include "Event.h"

namespace Thermo
{
    class WindowCloseEvent final : public Event
    {
    public:
        SET_EVENT_TYPE(WindowClose)
    };

    class WindowResizeEvent final : public Event
    {
    public:
        WindowResizeEvent(const int width, const int height)
            : m_Width(width), m_Height(height)
        {}

        SET_EVENT_TYPE(WindowResize)

        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }

    private:
        int m_Width, m_Height;
    };
}

#endif