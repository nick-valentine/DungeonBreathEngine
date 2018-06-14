#ifndef SCRIPT_AUDIO_H
#define SCRIPT_AUDIO_H

#include "lua.h"
#include "audio.h"

namespace lua {
    namespace l_audio {
        void add(lua_State *L);
        namespace music {
            int play(lua_State *L);
            int stop(lua_State *L);
            int playing(lua_State *L);
            int set_volume(lua_State *L);
        };
    };

};

#endif // SCRIPT_AUDIO_H
