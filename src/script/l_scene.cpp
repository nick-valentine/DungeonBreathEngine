#include "l_scene.h"

namespace lua {
    namespace l_scene {
        void add(lua_State *L)
        {
            LUALIB(lib) = {
                { "push", push },
                { "pop", pop },
                { "get_menu", get_menu },
                { "get_size", get_size },
                { NULL, NULL },
            };

            lua::add_lib(L, "scene", lib);
        }

        int get_menu(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -1);
            if (s == nullptr) {
                return 0;
            }
            lua_pushlightuserdata(L, s->get_menu());
            return 1;
        }

        int get_size(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -1);
            auto v = s->get_size();
            lua_newtable(L);
            auto t = lua_gettop(L);
            lua::add_num_field(L, t, "x", v.x);
            lua::add_num_field(L, t, "y", v.y);
            return 1;
        }

        int push(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -1);
            auto name = lua::get_string(L, -1);
            s->indicate_push(name);
            return 0;
        }

        int pop(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -1);
            s->indicate_pop();
            return 0;
        }
    }
};
