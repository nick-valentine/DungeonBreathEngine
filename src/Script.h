#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "Macros.h"

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

class Script
{
public:
	Script(std::string filename);
	~Script();

	void call();


	lua_State * s;
};

namespace lua {
	void stacktrace(lua_State *L);
	void error(lua_State *L, const char *fmt, ...);
};

#endif //SCRIPT_H