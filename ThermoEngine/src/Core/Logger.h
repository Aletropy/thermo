#ifndef THERMOENGINE_LOGGER_H
#define THERMOENGINE_LOGGER_H

namespace Thermo
{
    class Logger
    {
    public:
        Logger() = delete;
        Logger(const Logger&) = delete;

        static void Log(const char* fmt, ...);
    };
} // Thermo

#endif //THERMOENGINE_LOGGER_H
