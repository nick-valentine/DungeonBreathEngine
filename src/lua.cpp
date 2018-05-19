#include "lua.h"

#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void lua::stacktrace(lua_State *L)
{
	int top = lua_gettop(L);
	for (int i = 1; i <= top; ++i) {
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TSTRING:
			printf("`%s`", lua_tostring(L, i));
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
	std::cin.get();
	exit(1);
}