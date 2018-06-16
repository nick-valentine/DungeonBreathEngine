#include "l_render.h"

namespace lua {
    namespace sprite_manager {
        Container<render::SpriteSet>container = Container<render::SpriteSet>();

        void add(lua_State *L) {
            LUALIB(lib) = {
                { "get", get },
                { "release", release },
                { "make_sprite", make_sprite },
                { "remove_sprite", remove_sprite },
                { NULL, NULL }
            };
            lua::add_lib(L, "sprite_manager", lib);
        }

        int get(lua_State *L) {
            auto t = lua::get_string(L, -2);
            t = IMGDIR + t;
            auto size = (int) lua::get_num(L, -1);
            auto s = new render::SpriteSet(render::TextureMap::request(t), size);
            container.add(s);
            lua_pushlightuserdata(L, s);
            return 1;
        }

        int release(lua_State *L) {
            auto s = (render::SpriteSet *)lua::get_lightuserdata(L, -1);
            container.remove(s);
            return 0;
        }

        int make_sprite(lua_State *L) {
            auto s = (render::SpriteSet *)lua::get_lightuserdata(L, -3);
            sf::Vector2i pos;
            pos.x = lua::get_num_field(L, -2, "x");
            pos.y = lua::get_num_field(L, -2, "y");
            sf::Vector2i size;
            size.x = lua::get_num_field(L, -1, "x");
            size.y = lua::get_num_field(L, -1, "y");
            auto h = s->make_sprite(pos, size);
            auto spr = s->get_sprite(h);

            lua_pushlightuserdata(L, spr);
            return 1;
        }

        int remove_sprite(lua_State *L)
        {
            auto s = (render::SpriteSet *)lua::get_lightuserdata(L, -2);
            auto spr = (sf::Sprite *)lua::get_lightuserdata(L, -1);
            s->remove_sprite(spr);
            return 0;
        }
    };

    namespace sprite {
        void add(lua_State *L) {
            LUALIB(lib) = {
                { "set_position", set_position },
                { "draw", draw },
                { NULL, NULL },
            };
            lua::add_lib(L, "sprite", lib);
        }

        int set_position(lua_State *L) {
            auto spr = (sf::Sprite *)lua::get_lightuserdata(L, -2);
            auto left = lua::get_num_field(L, -1, "x");
            auto top = lua::get_num_field(L, -1, "y");
            spr->setPosition(left, top);
            return 0;
        }

        int draw(lua_State *L) {
            auto spr = (sf::Sprite *)lua::get_lightuserdata(L, -2);
            auto w = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
            w->draw(*spr);
            return 0;
        }

    };
};
