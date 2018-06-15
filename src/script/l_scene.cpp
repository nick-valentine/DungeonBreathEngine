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
                { "reset_camera", reset_camera },
                { "get_camera_center", get_camera_center },
                { "move_camera", move_camera },
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
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -2);
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

        int reset_camera(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -1);
            s->reset_camera();
            return 0;
        }

        int get_camera_center(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -1);
            auto c = s->get_camera_center();
            lua_newtable(L);
            auto t = lua_gettop(L);
            lua::add_num_field(L, t, "x", c.x);
            lua::add_num_field(L, t, "y", c.y);
            return 1;
        }

        int move_camera(lua_State *L)
        {
            auto s = (scene::Scene *)lua::get_lightuserdata(L, -2);
            auto x = lua::get_num_field(L, -1, "x");
            auto y = lua::get_num_field(L, -1, "y");
            s->move_camera(sf::Vector2f(x, y));
            return 0;
        }
    }
};
