#include "ThermoPch.h"
#include "Logger.h"

#include <cstdarg>
#include <cstdio>

namespace Thermo
{
    void Logger::BaseLog(int line, const char *file, LogLevel level, const char *fmt, ...)
    {
        std::string message = GetLogLevelString(level) + " [" + std::string(file) + ":" + std::to_string(line) + "] " + std::string(fmt);

        va_list args;
        va_start(args, fmt);
        vprintf(message.c_str(), args);
        va_end(args);

        printf("\n");
        fflush(stdout);
    }

    std::string Logger::GetLogLevelString(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Info: return "Info";
            case LogLevel::Warning: return "Warning";
            case LogLevel::Error: return "Error";
        }

        return "Unknown";
    }
} // Thermo