#ifndef THERMO_EVENT_H
#define THERMO_EVENT_H

#define SET_EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
virtual EventType GetEventType() const override { return GetStaticType(); } \
virtual const char* GetName() const override { return #type; }
#include <string>

namespace Thermo
{
    enum EventType
    {
        /* WINDOW RELATED EVENTS */
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        /* KEYBOARD RELATED EVENTS */
        KeyPressed,
        KeyTyped,
        KeyReleased,

        /* MOUSE RELATED EVENTS */
        MouseButtonPressed,
        MouseMoved,
        MouseScrolled,
        MouseButtonReleased
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        [[nodiscard]] virtual std::unique_ptr<Event> Clone() const = 0;


        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] std::string ToString() const { return GetName(); };

    };

    class EventDispatcher
    {
    public:
        explicit EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}


#endif