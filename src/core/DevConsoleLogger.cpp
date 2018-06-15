#include "DevConsoleLogger.h"
#include "Container.h"

namespace core {
    DevConsoleLogger::DevConsoleLogger()
    {

    }

    DevConsoleLogger::~DevConsoleLogger()
    {

    }

    void DevConsoleLogger::debug(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::VV, fmt, args);
        va_end(args);
    }

    void DevConsoleLogger::info(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::INFO, fmt, args);
        va_end(args);
    }

    void DevConsoleLogger::warn(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::WARN, fmt, args);
        va_end(args);
    }

    void DevConsoleLogger::error(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::ERROR, fmt, args);
        va_end(args);
    }

    void DevConsoleLogger::log(Logger::LogLevel level, const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(level, fmt, args);
        va_end(args);
    }

    void DevConsoleLogger::print(Logger::LogLevel level, const char *fmt, va_list args)
    {
        if (level >= Logger::logLevel) {
            app_container.get_console()->write(
                this->formatString(level, fmt, args)
            );
        }
    }
};
