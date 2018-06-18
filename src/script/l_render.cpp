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
                { "set_scale", set_scale },
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

        int set_scale(lua_State *L) {
            auto spr = (sf::Sprite *)lua::get_lightuserdata(L, -2);
            auto vec = lua::get_vec(L, -1);
            spr->setScale(vec);
            return 0;
        }

        int draw(lua_State *L) {
            auto spr = (sf::Sprite *)lua::get_lightuserdata(L, -2);
            auto w = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
            w->draw(*spr);
            return 0;
        }
    };

    namespace tile_set {
        Container<render::TileSet>container = Container<render::TileSet>();

        void add(lua_State *L) {
            LUALIB(lib) = {
                { "get", get },
                { "release", release },
                { "keys", keys },
                { "get_tile", get_tile },
                { NULL, NULL },
            };
            lua::add_lib(L, "tile_set", lib);
        }

        int get(lua_State *L) {
            auto t = lua::get_string(L, -1);
            auto s = new render::TileSet(t);
            container.add(s);
            lua_pushlightuserdata(L, s);
            return 1;
        }

        int release(lua_State *L) {
            auto s = (render::TileSet *)lua::get_lightuserdata(L, -1);
            container.remove(s);
            return 0;
        }

        int keys(lua_State *L) {
            auto s = (render::TileSet *)lua::get_lightuserdata(L, -1);
            auto k = s->get_keys();
            lua::put_int_array(L, k);
            return 1;
        }

        int get_tile(lua_State *L) {
            auto s = (render::TileSet *)lua::get_lightuserdata(L, -2);
            auto i = (int) lua::get_num(L, -1);
            auto t = s->spawn(render::TileType(i), sf::Vector2i(0, 0));
            lua::tile::container.add(t);
            lua_pushlightuserdata(L, t);
            return 1;
        }
    };

    namespace tile {
        Container<render::Tile>container = Container<render::Tile>();

        void add(lua_State *L) {
            LUALIB(lib) = {
                { "release", release },
                { "update", update },
                { "draw", draw },
                { "play", play },
                { "pause", pause },
                { "reset", reset },
                { "set_position", set_location },
                { "get_position", get_location },
                { "set_scale", set_scale },
                { "set_origin", set_origin },
                { "get_icon", get_icon },
                { NULL, NULL },
            };
            lua::add_lib(L, "tile", lib);
        }

        int release(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -1);
            container.remove(t);
            return 0;
        }

        int update(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -2);
            auto delta = lua::get_num(L, -1);
            t->update(delta);
            return 0;
        }

        int draw(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -2);
            auto w = (sf::RenderWindow *)lua::get_lightuserdata(L, -1);
            t->draw(*w);
            return 0;
        }

        int play(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -1);
            t->play();
            return 0;
        }

        int pause(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -1);
            t->pause();
            return 0;
        }

        int reset(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -1);
            t->reset();
            return 0;
        }

        int set_location(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -2);
            auto p = lua::get_vec(L, -1);
            t->set_location(sf::Vector2i(
                p.x, p.y
            ));
            return 0;
        }

        int get_location(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -1);
            auto p = t->get_location();
            sf::Vector2f pf;
            pf.x = p.x;
            pf.y = p.y;
            lua::put_vec(L, pf);
            return 1;
        }

        int set_scale(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -2);
            auto s = lua::get_vec(L, -1);
            t->set_scale(s);
            return 0;
        }

        int set_origin(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -2);
            auto s = lua::get_vec(L, -1);
            t->set_origin(s);
            return 0;
        }

        int get_icon(lua_State *L) {
            auto t = (render::Tile *)lua::get_lightuserdata(L, -1);
            auto s = t->get_icon();
            lua_pushlightuserdata(L, s);
            return 1;
        }
    };
};
