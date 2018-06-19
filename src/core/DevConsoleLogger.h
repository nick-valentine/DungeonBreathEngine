#ifndef DEVCONSOLE_LOGGER_HPP
#define DEVCONSOLE_LOGGER_HPP

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "Logger.h"

namespace core {
    class DevConsoleLogger : public Logger
    {
    public:
        DevConsoleLogger();
        virtual ~DevConsoleLogger();
        virtual void debug(const char *fmt, ...);
        virtual void info(const char *fmt, ...);
        virtual void warn(const char *fmt, ...);
        virtual void error(const char *fmt, ...);
        virtual void log(Logger::LogLevel level, const char *fmt, ...);
    protected:
        virtual void print(Logger::LogLevel level, const char *fmt, va_list args);
    };
};

#endif // DEVCONSOLE_LOGGER_HPP
