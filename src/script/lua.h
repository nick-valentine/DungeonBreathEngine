#ifndef LUA_H
#define LUA_H

#include <SFML/Graphics.hpp>
#include "Macros.h"
#include <string>
#include <vector>

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

namespace lua {
    void stacktrace(lua_State *L);
    void call_error(lua_State *L, const char *fmt, ...);
    void error(lua_State *L, const char *fmt, ...);
    void add_lib(lua_State *L, std::string name, const luaL_Reg *lib);

    int get_global_table(lua_State *L, std::string name);

    float get_num_field(lua_State *L, int pos, std::string key);
    void add_num_field(lua_State *L, int pos, std::string key, float value);

    /* general safe getters */
    float get_num(lua_State *L, int pos);
    std::string get_string(lua_State *L, int pos);
    void *get_userdata(lua_State *L, int pos);
    void *get_lightuserdata(lua_State *L, int pos);

    sf::FloatRect get_rect(lua_State *L, int pos);
    void put_rect(lua_State *L, sf::FloatRect rect);

    sf::Vector2f get_vec(lua_State *L, int pos);
    void put_vec(lua_State *L, sf::Vector2f vec);

    std::vector<float> get_float_array(lua_State *L, int pos);
    void put_int_array(lua_State *L, std::vector<int> arr);
    std::vector<std::string> get_string_array(lua_State *L, int pos);
    void put_string_array(lua_State *L, std::vector<std::string> arr);
};

#endif //LUA_H
