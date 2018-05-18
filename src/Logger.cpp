#include "Logger.h"

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
    char buffer[80];
    time_t rawTime;
    struct tm *timeInfo;
    timeInfo = localtime(&rawTime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeInfo);
    std::string time = buffer;
    return time;
}

void lua::logger::add(Logger *l, lua_State *S)
{
	static const struct luaL_Reg mylib[] = {
	{ "debug", debug },
	{ "info", info },
	{ "warn", warn },
	{ "error", error },
	{ NULL, NULL }
	};
	lua_getglobal(S, "logger");
	if (lua_isnil(S, -1)) {
		lua_pop(S, 1);
		lua_newtable(S);
	}
	luaL_setfuncs(S, mylib, 0);

	lua_pushlightuserdata(S, l);
	lua_setfield(S, -2, "log");

	lua_setglobal(S, "logger");	
}

int lua::logger::debug(lua_State *s)
{
	return log(Logger::LogLevel::VV, s);
}

int lua::logger::info(lua_State *s)
{
	return log(Logger::LogLevel::INFO, s);
}

int lua::logger::warn(lua_State *s)
{
	return log(Logger::LogLevel::WARN, s);
}

int lua::logger::error(lua_State *s)
{
	return log(Logger::LogLevel::ERROR, s);
}

int lua::logger::log(Logger::LogLevel level, lua_State *s)
{
	std::stringstream ss;

	Logger *l = (Logger *)lua_touserdata(s, 1);

	int top = lua_gettop(s);
	for (int i = 2; i <= top; ++i) {
		int t = lua_type(s, i);
		switch (t) {
		case LUA_TSTRING:
			ss<<lua_tostring(s, i)<<" ";
			break;
		case LUA_TBOOLEAN:
			ss<<lua_tonumber(s, i)<<" ";
			break;
		case LUA_TNUMBER:
			ss<<lua_tonumber(s, i)<<" ";
			break;
		default:
			lua::error(s, "type not supported for printing");
			break;
		}
	}
	l->log(level, ss.str().c_str());

	return 0;
}

