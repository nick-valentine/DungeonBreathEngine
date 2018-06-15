#ifndef SCRIPT_PLAY_H
#define SCRIPT_PLAY_H

#include "lua.h"

namespace lua {
    namespace world {
        void add(lua_State *L);
        int change_level(lua_State *L);
        int get_actorman(lua_State *L);
    };

    namespace actor {
        void add(lua_State *L);
        int get_rect(lua_State *L);
        int set_scale(lua_State *L);
        int set_origin(lua_State *L);
        int set_collision_bounds(lua_State *L);
        int get_velocity(lua_State *L);
        int set_velocity(lua_State *L);
        int set_tileset(lua_State *L);
        int pause_anim(lua_State *L);
        int play_anim(lua_State *L);
        int reset_anim(lua_State *L);
    };

    namespace actorman {
        void add(lua_State *L);
        int spawn(lua_State *L);
        int remove(lua_State *L);
        int clear(lua_State *L);
        int set_camera_target(lua_State *L);
        int get_camera_target(lua_State *L);
        int set_player(lua_State *L);
        int get_player(lua_State *L);
    };

};

#endif // SCRIPT_PLAY_H
