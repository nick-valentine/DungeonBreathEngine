#ifndef LUA_H
#define LUA_H

#include "Macros.h"
#include <string>

#if LINUX
// g++ links differently than windnows, windows mangles c names as well as it will compile
// lua as if it is c++, whereas linux compiles it as c and does not mangle names
extern "C" {
    #include "lua/lua.h"
    #include "lua/lualib.h"
    #include "lua/lauxlib.h"
}
#endif

#if WINDOWS
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#endif

namespace lua {
    void stacktrace(lua_State *L);
    void error(lua_State *L, const char *fmt, ...);
    /* assumes a table is at the top of the stack */
    float get_num_field(lua_State *L, std::string key);
    float get_num(lua_State *L, int pos);
};

#endif //LUA_H
