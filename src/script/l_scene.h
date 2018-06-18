#ifndef SCRIPT_SCENE_H
#define SCRIPT_SCENE_H

#include "lua.h"

namespace lua {
    namespace l_scene {
        void add(lua_State *L);
        int get_menu(lua_State *L);
        int get_size(lua_State *L);
        int push(lua_State *L);
        int pop(lua_State *L);
        int reset_camera(lua_State *L);
        int get_camera_center(lua_State *L);
        int move_camera(lua_State *L);
        int set_viewport(lua_State *L);
        int get_viewport(lua_State *L);
        int zoom_camera(lua_State *L);
        int apply_view(lua_State *L);
        int init_world(lua_State *L);
        int get_world(lua_State *L);
        int draw(lua_State *L);
    };

};

#endif // SCRIPT_SCENE_H
