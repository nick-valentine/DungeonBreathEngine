#ifndef SCRIPT_UI_H
#define SCRIPT_UI_H

#include "lua.h"

namespace lua {
    namespace l_ui {
        void add(lua_State *L);
        namespace menu {
            int set_current(lua_State *L);
            int add_text_button(lua_State *L);
            int add_sprite_button(lua_State *L);
            int add_label(lua_State *L);
            int add_label_raw(lua_State *L);
            int has_signal(lua_State *L);
            int signal_tag(lua_State *L);
            int signal_str(lua_State *L);
            int signal_int(lua_State *L);
            int clear(lua_State *L);
        };

        namespace menu_item {
            int raw(lua_State *L);
            int set_up(lua_State *L);
            int set_down(lua_State *L);
            int set_right(lua_State *L);
            int set_left(lua_State *L);
            int pair_items(lua_State *L);
            int get_tag(lua_State *L);
        };

        namespace label {
            int set_position(lua_State *L);
            int set_string(lua_State *L);
            int set_size(lua_State *L);

        };
    };

};

#endif // SCRIPT_UI_H
