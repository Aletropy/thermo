#ifndef THERMO_WINDOW_EVENTS_H
#define THERMO_WINDOW_EVENTS_H

#include "Event.h"

namespace Thermo
{
    class WindowCloseEvent final : public Event
    {
    public:
        SET_EVENT_TYPE(WindowClose)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<WindowCloseEvent>();
        }
    };

    class WindowResizeEvent final : public Event
    {
    public:
        WindowResizeEvent(const int width, const int height)
            : m_Width(width), m_Height(height)
        {}

        SET_EVENT_TYPE(WindowResize)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<WindowResizeEvent>(m_Width, m_Height);
        }


        [[nodiscard]] int GetWidth() const { return m_Width; }
        [[nodiscard]] int GetHeight() const { return m_Height; }

    private:
        int m_Width, m_Height;
    };
}

#endif