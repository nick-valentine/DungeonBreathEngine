#include "lua.h"

#include "core.h"

#include <string>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void lua::stacktrace(lua_State *L)
{
    std::stringstream ss;
    int top = lua_gettop(L);
    for (int i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING:
            ss<<"`"<<lua_tostring(L, i)<<"`";
            break;
        case LUA_TBOOLEAN:
            ss<<lua_tonumber(L, i);
            break;
        case LUA_TNUMBER:
            ss<<lua_tonumber(L, i);
            break;
        default:
            ss<<lua_typename(L, i);
            break;
        }
        ss<<" ";
    }
    core::app_container.get_logger()->error(ss.str().c_str());
    std::cout<<ss.str()<<std::endl;
}

void lua::error(lua_State *L, const char *fmt, ...)
{
    //lua_Debug ar;
    //lua_getstack(L, 1, &ar);
    //lua_getinfo(L, "nSl", &ar);
    //printf("Lua: error on line %s:%d\n", ar.source, ar.currentline);
    char buff[512];
    va_list argp;
    va_start(argp, fmt);
    vsprintf(buff, fmt, argp);
    va_end(argp);
    core::app_container.get_logger()->error(buff);
    std::cout<<buff<<std::endl;
    stacktrace(L);
    //lua_close(L);
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

sf::FloatRect lua::get_rect(lua_State *L, int pos)
{
    sf::FloatRect x;
    x.left = get_num_field(L, pos, "x");
    x.top = get_num_field(L, pos, "y");
    x.width = get_num_field(L, pos, "width");
    x.height = get_num_field(L, pos, "height");
    return x;
}

void lua::put_rect(lua_State *L, sf::FloatRect rect)
{
    lua_newtable(L);
    auto table = lua_gettop(L);
    lua_pushnumber(L, rect.left);
    lua_setfield(L, table, "x");
    lua_pushnumber(L, rect.top);
    lua_setfield(L, table, "y");
    lua_pushnumber(L, rect.width);
    lua_setfield(L, table, "width");
    lua_pushnumber(L, rect.height);
    lua_setfield(L, table, "height");
}

sf::Vector2f lua::get_vec(lua_State *L, int pos)
{
    sf::Vector2f x;
    x.x = get_num_field(L, pos, "x");
    x.y = get_num_field(L, pos, "y");
    return x;
}

void lua::put_vec(lua_State *L, sf::Vector2f vec)
{
    lua_newtable(L);
    auto table = lua_gettop(L);
    lua_pushnumber(L, vec.x);
    lua_setfield(L, table, "x");
    lua_pushnumber(L, vec.y);
    lua_setfield(L, table, "y");
}

std::vector<float> lua::get_float_array(lua_State *L, int pos)
{
    if (!lua_istable(L, pos)) {
        lua::error(L, "parameter must be array");
    }
    auto size = luaL_len(L, pos);
    std::vector<float> arr(size, 0);

    for (int i = 1; i <= size; ++i) {
        lua_rawgeti(L, pos, i);
        arr[i] = lua::get_num(L, -1);
        lua_pop(L, 1);
    }
    return arr;
}

std::vector<std::string> lua::get_string_array(lua_State *L, int pos)
{
    if (!lua_istable(L, pos)) {
        lua::error(L, "parameter must be array");
    }
    auto size = luaL_len(L, pos);
    std::cout<<size<<std::endl;
    std::vector<std::string> arr(size, "");

    for (int i = 1; i <= size; ++i) {
        lua_rawgeti(L, pos, i);
        arr[i] = lua::get_string(L, -1);
        lua_pop(L, 1);
    }
    return arr;
}

void lua::put_string_array(lua_State *L, std::vector<std::string> arr)
{
    lua_newtable(L);
    auto table = lua_gettop(L);
    for (size_t i = 0; i < arr.size(); ++i) {
        lua_pushstring(L, arr[i].c_str());
        lua_rawseti(L, table, i);
    }
}
