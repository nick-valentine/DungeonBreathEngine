#include "lua.h"

#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

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
    lua_Debug ar;
    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "nSl", &ar);
    printf("Lua: error on line %s:%d\n", ar.source, ar.currentline);
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    printf("\n");
    stacktrace(L);
    lua_close(L);
    exit(1);
}

void lua::add_lib(lua_State *L, std::string name, const luaL_Reg *lib)
{
    auto n = name.c_str();
    lua_getglobal(L, n);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
    }
    luaL_setfuncs(L, lib, 0);
    lua_setglobal(L, n);
}

int lua::get_global_table(lua_State *L, std::string name)
{
    auto n = name.c_str();
    lua_getglobal(L, n);
    if (lua_isnil(L, -1) || !lua_istable(L, -1)) {
        auto error_msg = name + " not table";
        lua::error(L, error_msg.c_str());
    }
    return lua_gettop(L);
}

float lua::get_num_field(lua_State *L, int pos, std::string key)
{
    if (pos < 0) {
        pos--;
    }
    lua_pushstring(L, key.c_str());
    lua_gettable(L, pos);
    if (!lua_isstring(L, -1)) {
        lua::error(L, "value at key %s not int", key.c_str());
    }
    auto x = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return x;
}

void lua::add_num_field(lua_State *L, int pos, std::string key, float value)
{
    auto k = key.c_str();
    lua_pushnumber(L, value);
    lua_setfield(L, pos, k);
}

float lua::get_num(lua_State *L, int pos)
{
    if (!lua_isnumber(L, pos)) {
        lua::error(L, "param not number");
    }
    return (float) lua_tonumber(L, pos);
}

std::string lua::get_string(lua_State *L, int pos)
{
    if (!lua_isstring(L, pos)) {
        lua::error(L, "parameter not string");
    }
    return lua_tostring(L, pos);
}

void *lua::get_userdata(lua_State *L, int pos)
{
    if (!lua_isuserdata(L, pos)) {
        lua::error(L, "parameter not userdata");
    }
    return lua_touserdata(L, pos);
}

void *lua::get_lightuserdata(lua_State *L, int pos)
{
    if (!lua_islightuserdata(L, pos)) {
        lua::error(L, "parameter not light userdata");
    }
    return lua_touserdata(L, pos);
}
