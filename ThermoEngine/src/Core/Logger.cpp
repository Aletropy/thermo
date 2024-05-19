#include "ThermoPch.h"
#include "Logger.h"

#include <cstdarg>
#include <cstdio>

namespace Thermo
{
    void Logger::Log(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);

        printf("\n");
    }
} // Thermo