#include "../../headers/Logger/Logger.h"

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
        ConfigLoader::getIntOption("logLevel", 0),
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
    char buffer[80];
    time_t rawTime;
    struct tm *timeInfo;
    timeInfo = localtime(&rawTime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeInfo);
    std::string time = buffer;
    return time;
}
