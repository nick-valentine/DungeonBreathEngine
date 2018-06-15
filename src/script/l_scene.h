#ifndef SCRIPT_SCENE_H
#define SCRIPT_SCENE_H

#include "lua.h"
#include "scene.h"

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
    };

};

#endif // SCRIPT_SCENE_H
