#ifndef LUA_H
#define LUA_H

#include "Macros.h"
#include <string>

#define LUALIB(a) static const struct luaL_Reg a []

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

#include "core.h"

namespace lua {
    void stacktrace(lua_State *L);
    void error(lua_State *L, const char *fmt, ...);
    void add_lib(lua_State *L, std::string name, const luaL_Reg *lib);

    int get_global_table(lua_State *L, std::string name);

    /* @todo: deprecate: assumes a table is at the top of the stack */
    float get_num_field(lua_State *L, std::string key);
    float get_num_field(lua_State *L, int pos, std::string key);
    void add_num_field(lua_State *L, int pos, std::string key, float value);

    /* general safe getters */
    float get_num(lua_State *L, int pos);
    std::string get_string(lua_State *L, int pos);
    void *get_userdata(lua_State *L, int pos);
    void *get_lightuserdata(lua_State *L, int pos);
};

#endif //LUA_H
