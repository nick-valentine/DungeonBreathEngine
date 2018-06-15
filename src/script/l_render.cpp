#include "l_render.h"

namespace lua {
    namespace sprite_manager {
        Container<render::SpriteSet>container = Container<render::SpriteSet>();

        void add(lua_State *L) {
            LUALIB(lib) = {
                { "get", get },
                { "release", release },
                { "make_sprite", make_sprite },
                { "get_sprite", get_sprite },
                { NULL, NULL }
            };
            lua::add_lib(L, "sprite_manager", lib);
        }

        int get(lua_State *L) {

            return 0;
        }

        int release(lua_State *L) {

            return 0;
        }

        int make_sprite(lua_State *L) {

            return 0;
        }

        int get_sprite(lua_State *L) {

            return 0;
        }
    };

    namespace sprite {
        Container<sf::Sprite>container = Container<sf::Sprite>();

        void add(lua_State *L) {
            LUALIB(lib) = {
                { "release", release },
                { "set_position", set_position },
            };
            lua::add_lib(L, "sprite", lib);
        }

        int release(lua_State *L) {
            return 0;
        }

        int set_position(lua_State *L) {
            return 0;
        }

    };
};
