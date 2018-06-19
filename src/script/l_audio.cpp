#include "l_audio.h"

namespace lua {
    namespace l_audio {
        void add (lua_State *L) {
            LUALIB(lib) = {
                { "play", music::play },
                { "stop", music::stop },
                { "playing", music::playing },
                { "set_volume", music::set_volume },
                { NULL, NULL },
            };
            lua::add_lib(L, "music", lib);
        }

        namespace music {
            int play(lua_State *L) {
                auto name = lua::get_string(L, -1);
                audio::MusicManager::play(name);
                return 0;
            }

            int stop(lua_State *L) {
                audio::MusicManager::stop();
                return 0;
            }

            int playing(lua_State *L) {
                auto name = audio::MusicManager::playing();
                lua_pushstring(L, name.c_str());
                return 1;
            }

            int set_volume(lua_State *L) {
                auto v = lua::get_num(L, -1);
                audio::MusicManager::set_volume(v);
                return 0;
            }
        };
    };
};
