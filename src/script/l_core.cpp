#include "l_core.h"

namespace lua {
    namespace config {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                {"get_int", get_int},
                {"get_string", get_string},
                {"set", set},
                {"save", save},
                {NULL, NULL}
            };
            lua::add_lib(L, "config", lib);
        }

        int get_int(lua_State *L)
        {
            auto c = lua::get_string(L, -2);
            auto d = lua::get_num(L, -1);
            int n = core::ConfigLoader::get_int_option(c, d);
            lua_pushnumber(L, n);

            return 1;
        }

        int get_string(lua_State *L)
        {
            auto c = lua::get_string(L, -2);
            auto d = lua::get_string(L, -1);
            auto s = core::ConfigLoader::get_string_option(c, d);
            lua_pushstring(L, s.c_str());

            return 1;
        }

        int set(lua_State *L)
        {
            auto c = lua::get_string(L, -2);
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
            lua::logger::add(L);
            lua::input::add(L);
            lua::lang::add(L);
            lua::index::add(L);
        }
    };

    namespace input {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                { "is_key_pressed", is_key_pressed },
				{ "get_input", get_input },
				{ "set_active_joystick", set_active_joystick },
                { NULL, NULL }
            };
            lua::add_lib(L, "input", lib);

            auto table = lua::get_global_table(L, "input");
            lua::add_num_field(L, table, "up", core::Input::up);
            lua::add_num_field(L, table, "down", core::Input::down);
            lua::add_num_field(L, table, "left", core::Input::left);
            lua::add_num_field(L, table, "right", core::Input::right);
            lua::add_num_field(L, table, "escape", core::Input::escape);
            lua::add_num_field(L, table, "accept", core::Input::accept);
            lua::add_num_field(L, table, "fire", core::Input::fire);
            lua::add_num_field(L, table, "alt_fire", core::Input::alt_fire);
            lua::add_num_field(L, table, "num_keys", core::Input::num_keys);

            lua_setglobal(L, "input");
        }

        int is_key_pressed(lua_State *L)
        {
            auto key = (int) lua::get_num(L, -1);
            auto pressed = core::app_container.get_input()->is_key_pressed(core::Input::Key(key));

            lua_pushnumber(L, pressed);
            return 1;
        }

		int get_input(lua_State *L)
		{
			auto dsn = core::app_container.get_input()->get_input();
			lua_pushstring(L, dsn.c_str());
			return 1;
		}

		int set_active_joystick(lua_State *L)
		{
			auto i = (int)lua::get_num(L, -1);
			core::app_container.get_input()->set_active_joystick(i);
			return 0;
		}
    };

    namespace lang {
        void add(lua_State *S)
        {
            LUALIB(lib) = {
                { "next", next },
                { "prev", prev },
                { NULL, NULL },
            };
            lua::add_lib(S, "lang", lib);
        }

        int next(lua_State *S)
        {
            auto l = core::StringProvider::next_lang();
            lua_pushstring(S, l.c_str());
            return 1;
        }

        int prev(lua_State *S)
        {
            auto l = core::StringProvider::prev_lang();
            lua_pushstring(S, l.c_str());
            return 1;
        }
    }

    namespace logger {
        void add(lua_State *S)
        {
            LUALIB(lib) = {
                { "debug", debug },
                { "info", info },
                { "warn", warn },
                { "error", error },
                { NULL, NULL }
            };
            lua::add_lib(S, "logger", lib);
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
                case LUA_TNIL:
                    ss<<"<nil>";
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

    namespace index {
        Container<core::Index> container = Container<core::Index>();

        void add(lua_State *L) {
            LUALIB(lib) = {
                { "get", get },
                { "release", release },
                { "add", insert },
                { "remove", remove },
                { "save", save },
                { "all", all },
                { NULL, NULL },
            };
            lua::add_lib(L, "index", lib);
        }

        int get(lua_State *L) {
            auto s = lua::get_string(L, -1);
            auto tmp = new core::Index(s);
            container.add(tmp);
            lua_pushlightuserdata(L, tmp);
            return 1;
        }

        int release(lua_State *L) {
            auto i = (core::Index *)lua::get_lightuserdata(L, -1);
            container.remove(i);
            return 0;
        }

        int insert(lua_State *L) {
            auto i = (core::Index *)lua::get_lightuserdata(L, -2);
            auto s = lua::get_string(L, -1);
            i->add(s);
            return 0;
        }

        int remove(lua_State *L) {
            auto i = (core::Index *)lua::get_lightuserdata(L, -2);
            auto s = lua::get_string(L, -1);
            i->remove(s);
            return 0;
        }

        int save(lua_State *L) {
            auto i = (core::Index *)lua::get_lightuserdata(L, -1);
            i->save();
            return 0;
        }

        int all(lua_State *L) {
            auto i = (core::Index *)lua::get_lightuserdata(L, -1);
            auto s = i->get();
            std::vector<std::string> str_arr;
            for (const auto &v : s) {
                str_arr.push_back(v);
            }
            lua::put_string_array(L, str_arr);
            return 1;
        }
    };
};
