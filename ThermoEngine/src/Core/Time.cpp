#include "ThermoPch.h"
#include "Time.h"

#include <GLFW/glfw3.h>

namespace Thermo
{
    double Time::m_DeltaTime = 0.0;
    double Time::m_LastTime = 0.0;

    float Time::CalculateDeltaTime()
    {
        double now = glfwGetTime();
        m_DeltaTime = (now - m_LastTime);
        m_LastTime = now;

        return (float)m_DeltaTime;
    }
} // Thermo