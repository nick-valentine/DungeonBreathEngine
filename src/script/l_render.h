#ifndef SCRIPT_RENDER_H

#include "lua.h"
#include "render.h"
#include "Container.h"

namespace lua {
    namespace sprite_manager {
        extern Container<render::SpriteSet> container;

        void add(lua_State *L);

        int get(lua_State *L);
        int release(lua_State *L);
        int make_sprite(lua_State *L);
        int remove_sprite(lua_State *L);
    };

    namespace sprite {
        void add(lua_State *L);

        int set_position(lua_State *L);
        int set_scale(lua_State *L);
        int draw(lua_State *L);
    };

    namespace tile_set {
        extern Container<render::TileSet> container;

        void add(lua_State *L);

        int get(lua_State *L);
        int release(lua_State *L);
        int get_tile(lua_State *L);
    };

    namespace tile {
        extern Container<render::Tile> container;

        void add(lua_State *L);

        int release(lua_State *L);
        int update(lua_State *L);
        int draw(lua_State *L);
        int play(lua_State *L);
        int pause(lua_State *L);
        int reset(lua_State *L);
        int set_location(lua_State *L);
        int get_location(lua_State *L);
        int set_scale(lua_State *L);
        int set_origin(lua_State *L);
    }
};

#define SCRIPT_RENDER_H
#endif // SCRIPT_RENDER_H
