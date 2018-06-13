#include "l_ui.h"

void lua::l_ui::add(lua_State *L)
{
    LUALIB(lib) = {
        { "set_current", menu::set_current },
        { "add_text_button", menu::add_text_button },
        { "has_signal", menu::has_signal },
        { "signal_str", menu::signal_str },
        { "signal_int", menu::signal_int },
        { NULL, NULL },
    };

    lua::add_lib(L, "menu", lib);
}

namespace lua {
    namespace l_ui {
        namespace menu {
            int set_current(lua_State *L) {
                auto m = (ui::Menu *)lua::get_lightuserdata(L, -2);
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                m->set_current(mi);
                return 0;
            }

            int add_text_button(lua_State *L) {
                auto m = (ui::Menu *)lua::get_lightuserdata(L, -4);
                auto tag = lua::get_string(L, -3);
                auto x = lua::get_num_field(L, -2, "x");
                auto y = lua::get_num_field(L, -2, "y");
                auto content_key = lua::get_string(L, -1);
                auto p = m->add_text_button(tag, sf::Vector2i(x, y), content_key);
                lua_pushlightuserdata(L, p);
                return 1;
            }

            int has_signal(lua_State *L) {
                auto m = (ui::Menu *)lua::get_lightuserdata(L, -1);
                auto s = m->has_signal();
                lua_pushnumber(L, s);
                return 1;
            }

            int signal_str(lua_State *L) {
                auto m = (ui::Menu *)lua::get_lightuserdata(L, -1);
                auto s = m->signal_str();
                lua_pushstring(L, s.c_str());
                return 1;
            }

            int signal_int(lua_State *L) {
                auto m = (ui::Menu *)lua::get_lightuserdata(L, -1);
                auto s = m->signal_int();
                lua_pushnumber(L, s);
                return 1;
            }
        };

        namespace menu_item {
            int raw(lua_State *L) {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                auto r = mi->raw();
                lua_pushlightuserdata(L, r);
                return 1;
            }

            int set_up(lua_State *L)
            {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -2);
                auto other = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                mi->set_up(other);
                return 0;
            }

            int set_down(lua_State *L)
            {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -2);
                auto other = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                mi->set_down(other);
                return 0;
            }

            int set_right(lua_State *L)
            {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -2);
                auto other = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                mi->set_right(other);
                return 0;
            }

            int set_left(lua_State *L)
            {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -2);
                auto other = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                mi->set_left(other);
                return 0;
            }

            int pair_items(lua_State *L)
            {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -3);
                auto other = (ui::MenuItem *)lua::get_lightuserdata(L, -2);
                auto s = (int) lua::get_num(L, -1);
                ui::pair_items(mi, other, ui::MenuItem::side(s));
                return 0;
            }

            int get_tag(lua_State *L)
            {
                auto mi = (ui::MenuItem *)lua::get_lightuserdata(L, -1);
                auto s = mi->get_tag();
                lua_pushstring(L, s.c_str());
                return 1;
            }
        };
    };

};
