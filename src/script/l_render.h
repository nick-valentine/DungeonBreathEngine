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
    };
};

#define SCRIPT_RENDER_H
#endif // SCRIPT_RENDER_H
