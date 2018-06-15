#ifndef SCRIPT_IMGUI_H
#define SCRIPT_IMGUI_H

#include "lua.h"
#include "imgui.h"

namespace lua {
    namespace l_imgui {
        void add(lua_State *L);

        int begin(lua_State *L);
        int end(lua_State *L);
        int button(lua_State *L);
        int checkbox(lua_State *L);
        int progressbar(lua_State *L);
    };
};

#endif // SCRIPT_IMGUI_H
