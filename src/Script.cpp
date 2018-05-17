#include "Script.h"

Script::Script(std::string filename)
{
	s = luaL_newstate();
	luaL_openlibs(s);
	std::string full_path = SCRIPTDIR;
	full_path += filename;
	luaL_loadfile(s, full_path.c_str());
}

Script::~Script()
{
	lua_close(s);
}

void Script::call()
{
	lua_call(s, 0, 0);
}

void lua::stacktrace(lua_State *L)
{
	int top = lua_gettop(L);
	for (int i = 1; i < top; ++i) {
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TSTRING:
			printf("`%s", lua_tostring(L, i));
			break;
		case LUA_TBOOLEAN:
			printf("%g", lua_tonumber(L, i));
			break;
		case LUA_TNUMBER:
			printf("%g", lua_tonumber(L, i));
			break;
		default:
			printf("%s", lua_typename(L, t));
			break;
		}
		printf("  ");
	}
	printf("\n");
}

void lua::error(lua_State *L, const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	printf("\n");
	stacktrace(L);
	lua_close(L);
	exit(1);
}