#ifndef LUA_H
#define LUA_H


#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

namespace lua {
	void stacktrace(lua_State *L);
	void error(lua_State *L, const char *fmt, ...);
};

#endif //LUA_H