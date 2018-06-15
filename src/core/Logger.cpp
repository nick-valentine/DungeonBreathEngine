#include "Logger.h"
#include "Container.h"

namespace core {

    const std::string Logger::levelStrings[5] = {
        "NONE",
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };

    int Logger::logLevel = 0;

    void Logger::configure()
    {
        //do not let errors be suppressed
        Logger::logLevel = std::max(
            ConfigLoader::get_int_option("logLevel", 0),
            int(WARN)
        );
    }

    std::string Logger::formatString(LogLevel level, const char *fmt, va_list args)
    {
        char b[256];
        vsnprintf(b, 255, fmt, args);

        std::string formatted = "[" +
            Logger::levelStrings[level] +
            ": " +
            this->getTime() +
            "]"
        ;
        formatted += b;
        return formatted;
    }

    std::string Logger::getTime()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss<<std::put_time(std::localtime(&now_c), "%F %T");
        return ss.str();
    }
}


