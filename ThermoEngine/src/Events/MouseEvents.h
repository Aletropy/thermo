#ifndef MOUSEEVENTS_H
#define MOUSEEVENTS_H
#include "Event.h"

namespace Thermo
{
    class MouseButtonPressedEvent final : public Event
    {
    public:
        explicit MouseButtonPressedEvent(const int button)
            : m_Button(button)
        {}

        SET_EVENT_TYPE(MouseButtonPressed)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<MouseButtonPressedEvent>(m_Button);
        }

        [[nodiscard]] int GetButton() const { return m_Button; }

    private:
        int m_Button;
    };

    class MouseButtonReleasedEvent final : public Event
    {
    public:
        explicit MouseButtonReleasedEvent(const int button)
            : m_Button(button)
        {}

        SET_EVENT_TYPE(MouseButtonReleased)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<MouseButtonReleasedEvent>(m_Button);
        }

        [[nodiscard]] int GetButton() const { return m_Button; }

    private:
        int m_Button;
    };

    class MouseMovedEvent final : public Event
    {
    public:
        explicit MouseMovedEvent(const double x, const double y)
            : m_X(x), m_Y(y)
        {}

        SET_EVENT_TYPE(MouseMoved)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<MouseMovedEvent>(m_X, m_Y);
        }

        [[nodiscard]] double GetX() const { return m_X; }
        [[nodiscard]] double GetY() const { return m_Y; }

    private:
        double m_X, m_Y;
    };

    class MouseScrolledEvent final : public Event
    {
    public:
        explicit MouseScrolledEvent(const double x, const double y)
            : m_X(x), m_Y(y)
        {}

        SET_EVENT_TYPE(MouseScrolled)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<MouseScrolledEvent>(m_X, m_Y);
        }

        [[nodiscard]] double GetX() const { return m_X; }
        [[nodiscard]] double GetY() const { return m_Y; }

    private:
        double m_X, m_Y;
    };
}

#endif //MOUSEEVENTS_H
