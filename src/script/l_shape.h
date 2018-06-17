#ifndef SCRIPT_SHAPE_H
#define SCRIPT_SHAPE_H

#include <SFML/Graphics.hpp>
#include "lua.h"
#include "Container.h"

namespace lua {
    namespace shape {
        void add(lua_State *L);

        namespace rect {
            extern Container<sf::RectangleShape> container;

            void add(lua_State *L);

            int get(lua_State *L);
            int release(lua_State *L);
            int set_size(lua_State *L);
            int set_position(lua_State *L);
            int set_fill_color(lua_State *L);
            int set_outline_color(lua_State *L);
            int set_outline_thickness(lua_State *L);
            int draw(lua_State *L);
        };
    };
};

#endif // SCRIPT_SHAPE_H
