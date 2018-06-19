#include "l_shape.h"

namespace lua {
    namespace shape {

        void add(lua_State *L)
        {
            rect::add(L);
        }

        namespace rect {
            Container<sf::RectangleShape> container = Container<sf::RectangleShape>();

            void add(lua_State *L) {
                LUALIB(lib) = {
                    { "get", get },
                    { "release", release },
                    { "set_size", set_size },
                    { "set_position", set_position },
                    { "set_fill_color", set_fill_color },
                    { "set_outline_color", set_outline_color },
                    { "set_outline_thickness", set_outline_thickness },
                    { "draw", draw },
                    { NULL, NULL },
                };
                lua::add_lib(L, "rectangle_shape", lib);
            }

            int get(lua_State *L)
            {
                auto s = new sf::RectangleShape();
                container.add(s);
                lua_pushlightuserdata(L, s);
                return 1;
            }

            int release(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -1);
                container.remove(s);
                return 0;
            }

            int set_size(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -2);
                auto v = lua::get_vec(L, -1);
                s->setSize(v);
                return 0;
            }

            int set_position(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -2);
                auto v = lua::get_vec(L, -1);
                s->setPosition(v);
                return 0;
            }

            int set_fill_color(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -2);
                auto r = (int) lua::get_num_field(L, -1, "r");
                auto g = (int) lua::get_num_field(L, -1, "g");
                auto b = (int) lua::get_num_field(L, -1, "b");
                auto a = 255;
                lua_pushstring(L, "a");
                lua_gettable(L, -2);
                if (!lua_isnil(L, -1)) {
                    a = lua_tonumber(L, -1);
                }

                s->setFillColor(sf::Color(r, g, b, a));
                return 0;
            }

            int set_outline_color(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -2);
                auto r = (int) lua::get_num_field(L, -1, "r");
                auto g = (int) lua::get_num_field(L, -1, "g");
                auto b = (int) lua::get_num_field(L, -1, "b");
                auto a = 255;
                lua_pushstring(L, "a");
                lua_gettable(L, -2);
                if (!lua_isnil(L, -1)) {
                    a = lua_tonumber(L, -1);
                }
                s->setOutlineColor(sf::Color(r, g, b, a));
                return 0;
            }

            int set_outline_thickness(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -2);
                auto i = (int) lua::get_num(L, -1);
                s->setOutlineThickness(i);
                return 0;
            }

            int draw(lua_State *L)
            {
                auto s = (sf::RectangleShape *)lua::get_lightuserdata(L, -2);
                auto w = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
                w->draw(*s);
                return 0;
            }

        };
    };
};
