#include "l_core.h"

namespace lua {
    namespace config {
        void add(lua_State *L)
        {
            static const struct luaL_Reg mylib[] = {
                {"get_int", get_int},
                {"get_string", get_string},
                {"set", set},
                {"save", save},
                {NULL, NULL}
            };
            lua_getglobal(L, "config");
            if (lua_isnil(L, -1)) {
                lua_pop(L, 1);
                lua_newtable(L);
            }
            luaL_setfuncs(L, mylib, 0);
            lua_setglobal(L, "config");
        }

        int get_int(lua_State *L)
        {
            if (!lua_isstring(L, -2)) {
                error(L, "config.get_int arg 1 not string");
            }
            auto c = lua_tostring(L, -2);
            if (!lua_isnumber(L, -1)) {
                error(L, "config.get_int arg 2 not int");
            }
            auto d = lua_tonumber(L, -1);

            int n = core::ConfigLoader::get_int_option(c, d);

            lua_pushnumber(L, n);

            return 1;
        }

        int get_string(lua_State *L)
        {
            if (!lua_isstring(L, -2)) {
                error(L, "config.get_string arg 1 not string");
            }
            auto c = lua_tostring(L, -2);
            if (!lua_isstring(L, -1)) {
                error(L, "config.get_string arg 2 not string");
            }
            auto d = lua_tostring(L, -1);

            auto s = core::ConfigLoader::get_string_option(c, d);

            lua_pushstring(L, s.c_str());

            return 1;
        }

        int set(lua_State *L)
        {
            if (!lua_isstring(L, -2)) {
                error(L, "config.set arg 1 not string");
            }
            auto c = lua_tostring(L, -2);
            if (lua_isnumber(L, -1)) {
                auto d = lua_tonumber(L, -1);
                core::ConfigLoader::mutate_option(c, d);
                return 0;
            } else if (lua_isstring(L, -1)) {
                auto d = lua_tostring(L, -1);
                core::ConfigLoader::mutate_option(c, d);
                return 0;
            } else {
                error(L, "config.set arg 2 not int or string");
            }
            return -1;
        }

        int save(lua_State *L)
        {
            core::ConfigLoader::save();
            return 0;
        }
    };

    namespace container {
        void add(lua_State *L)
        {
            lua::config::add(L);
            lua::logger::add(core::app_container.get_logger(), L);
            lua::input::add(core::app_container.get_input(), L);
        }
    };

    namespace input {
        void add(core::Input *i, lua_State *s)
        {
            static const struct luaL_Reg mylib[] = {
                { "is_key_pressed", is_key_pressed },
                { NULL, NULL }
            };
            lua_getglobal(s, "input");
            if (lua_isnil(s, -1)) {
                lua_pop(s, 1);
                lua_newtable(s);
            }
            luaL_setfuncs(s, mylib, 0);

            lua_pushlightuserdata(s, i);
            lua_setfield(s, -2, "device");

            lua_pushnumber(s, core::Input::up);
            lua_setfield(s, -2, "up");

            lua_pushnumber(s, core::Input::down);
            lua_setfield(s, -2, "down");

            lua_pushnumber(s, core::Input::left);
            lua_setfield(s, -2, "left");

            lua_pushnumber(s, core::Input::right);
            lua_setfield(s, -2, "right");

            lua_pushnumber(s, core::Input::escape);
            lua_setfield(s, -2, "escape");

            lua_pushnumber(s, core::Input::accept);
            lua_setfield(s, -2, "accept");

            lua_pushnumber(s, core::Input::fire);
            lua_setfield(s, -2, "fire");

            lua_pushnumber(s, core::Input::alt_fire);
            lua_setfield(s, -2, "alt_fire");

            lua_pushnumber(s, core::Input::num_keys);
            lua_setfield(s, -2, "num_keys");

            lua_setglobal(s, "input");
        }

        int is_key_pressed(lua_State *s)
        {
            core::Input *i = (core::Input *)lua_touserdata(s, 1);
            if (!lua_isnumber(s, 2)) {
                error(s, "arg 2 expected to be number");
            }
            auto key = (int) lua_tonumber(s, 2);

            auto pressed = i->is_key_pressed(core::Input::Key(key));

            lua_pushnumber(s, pressed);

            return 1;
        }
    };

    namespace logger {
        void add(core::Logger *l, lua_State *S)
        {
            static const struct luaL_Reg mylib[] = {
            { "debug", debug },
            { "info", info },
            { "warn", warn },
            { "error", error },
            { NULL, NULL }
            };
            lua_getglobal(S, "logger");
            if (lua_isnil(S, -1)) {
                lua_pop(S, 1);
                lua_newtable(S);
            }
            luaL_setfuncs(S, mylib, 0);

            lua_pushlightuserdata(S, l);
            lua_setfield(S, -2, "log");

            lua_setglobal(S, "logger"); 
        }

        int debug(lua_State *s)
        {
            return log(core::Logger::LogLevel::VV, s);
        }

        int info(lua_State *s)
        {
            return log(core::Logger::LogLevel::INFO, s);
        }

        int warn(lua_State *s)
        {
            return log(core::Logger::LogLevel::WARN, s);
        }

        int error(lua_State *s)
        {
            return log(core::Logger::LogLevel::ERROR, s);
        }

        int log(core::Logger::LogLevel level, lua_State *s)
        {
            std::stringstream ss;

            int top = lua_gettop(s);
            for (int i = 1; i <= top; ++i) {
                int t = lua_type(s, i);
                switch (t) {
                case LUA_TSTRING:
                    ss<<lua_tostring(s, i)<<" ";
                    break;
                case LUA_TBOOLEAN:
                    ss<<lua_tonumber(s, i)<<" ";
                    break;
                case LUA_TNUMBER:
                    ss<<lua_tonumber(s, i)<<" ";
                    break;
                default:
                    lua::error(s, "type not supported for printing");
                    break;
                }
            }
            core::app_container.get_logger()->log(level, ss.str().c_str());

            return 0;
        }
    };

};
