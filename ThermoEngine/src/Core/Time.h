#ifndef THERMOENGINE_TIME_H
#define THERMOENGINE_TIME_H

namespace Thermo
{

    class Time
    {
    public:
        Time() = delete;
        Time(const Time&&) = delete;
    private:
        static float DeltaTime() { return (float)m_DeltaTime; }
        static float CalculateDeltaTime();
    private:
        static double m_LastTime;
        static double m_DeltaTime;

        friend class Application;
    };

} // Thermo

#endif //THERMOENGINE_TIME_H
