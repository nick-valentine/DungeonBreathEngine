#include "ConsoleLogger.h"

namespace core {
    ConsoleLogger::ConsoleLogger()
    {

    }

    ConsoleLogger::~ConsoleLogger()
    {

    }

    void ConsoleLogger::debug(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::VV, fmt, args);
        va_end(args);
    }

    void ConsoleLogger::info(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::INFO, fmt, args);
        va_end(args);
    }

    void ConsoleLogger::warn(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::WARN, fmt, args);
        va_end(args);
    }

    void ConsoleLogger::error(const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(Logger::ERROR, fmt, args);
        va_end(args);
    }

    void ConsoleLogger::log(Logger::LogLevel level, const char *fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        this->print(level, fmt, args);
        va_end(args);
    }

    void ConsoleLogger::print(Logger::LogLevel level, const char *fmt, va_list args)
    {
        if (level >= Logger::logLevel) {
            printf("%s\n",
                this->formatString(level, fmt, args).c_str()
            );
        }
    }
};
