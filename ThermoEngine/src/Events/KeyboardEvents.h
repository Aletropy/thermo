#ifndef THERMO_KEYBOARD_EVENTS_H
#define THERMO_KEYBOARD_EVENTS_H
#include "Event.h"
#include "GLFW/glfw3.h"

namespace Thermo
{
    class KeyPressedEvent final : public Event
    {
    public:
        KeyPressedEvent(const int keycode, const int repeatCount)
            : m_KeyCode(keycode), m_RepeatCount(repeatCount)
        {}

        SET_EVENT_TYPE(KeyPressed)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<KeyPressedEvent>(m_KeyCode, m_RepeatCount);
        }

        [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }
        [[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

    private:
        int m_KeyCode;
        int m_RepeatCount;
    };

    class KeyReleasedEvent final : public Event
    {
    public:
        explicit KeyReleasedEvent(const int keycode)
            : m_KeyCode(keycode)
        {}

        SET_EVENT_TYPE(KeyReleased)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<KeyReleasedEvent>(m_KeyCode);
        }

        [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

    private:
        int m_KeyCode;
    };

    class KeyTypedEvent final : public Event
    {
    public:
        explicit KeyTypedEvent(const int keycode)
            : m_KeyCode(keycode)
        {}

        SET_EVENT_TYPE(KeyTyped)

        [[nodiscard]] std::unique_ptr<Event> Clone() const override {
            return std::make_unique<KeyTypedEvent>(m_KeyCode);
        }

        [[nodiscard]] int GetKeyCode() const { return m_KeyCode; }
    private:
        int m_KeyCode;
    };
}

#endif
