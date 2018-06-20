#ifndef SCRIPT_AUDIO_H
#define SCRIPT_AUDIO_H

#include <SFML/System.hpp>

#include "lua.h"
#include "audio.h"
#include "Container.h"

namespace lua {
    namespace l_audio {
        void add(lua_State *L);
        namespace music {
            int play(lua_State *L);
            int stop(lua_State *L);
            int playing(lua_State *L);
            int set_volume(lua_State *L);
        };

        namespace sound {
            extern Container<sf::Sound> container;

            int get(lua_State *L);
            int release(lua_State *L);
            int play(lua_State *L);
            int pause(lua_State *L);
            int stop(lua_State *L);
            int set_playing_offset(lua_State *L);
            int get_playing_offset(lua_State *L);
            int set_loop(lua_State *L);
            int get_loop(lua_State *L);
            int set_volume(lua_State *L);
            int is_playing(lua_State *L);
        };
    };

};

#endif // SCRIPT_AUDIO_H
