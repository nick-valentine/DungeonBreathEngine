#ifndef LUA_H
#define LUA_H

#include <string>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

namespace lua {
	void stacktrace(lua_State *L);
	void error(lua_State *L, const char *fmt, ...);
	/* assumes a table is at the top of the stack */
	int get_int_field(lua_State *L, std::string key);
};

#endif //LUA_H