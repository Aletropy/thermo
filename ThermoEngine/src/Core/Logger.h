#ifndef THERMOENGINE_LOGGER_H
#define THERMOENGINE_LOGGER_H

#include "Core/Base.h"
#include <string>

namespace Thermo
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    class Logger
    {
    public:
        STATIC_CONSTRUCTORS(Logger)

        static void BaseLog(int line, const char* file, LogLevel level, const char* fmt, ...);

        static std::string GetLogLevelString(LogLevel level);
    };
} // Thermo

#define THERMO_LOG(fmt, ...) Thermo::Logger::BaseLog(__LINE__, __FILE__, Thermo::LogLevel::Info, fmt, __VA_ARGS__)
#define THERMO_WARN(fmt, ...) Thermo::Logger::BaseLog(__LINE__, __FILE__, Thermo::LogLevel::Warning, fmt, __VA_ARGS__)
#define THERMO_ERROR(fmt, ...) Thermo::Logger::BaseLog(__LINE__, __FILE__, Thermo::LogLevel::Error, fmt, __VA_ARGS__)

#define THERMO_ASSERT(x, fmt, ...) if(!(x)) Thermo::Logger::BaseLog(__LINE__, __FILE__, Thermo::LogLevel::Error, fmt, __VA_ARGS__)

#endif //THERMOENGINE_LOGGER_H
