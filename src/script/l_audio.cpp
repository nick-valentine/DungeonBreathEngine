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

            LUALIB(sound_lib) = {
                { "get", sound::get },
                { "release", sound::release },
                { "play", sound::play },
                { "pause", sound::pause },
                { "stop", sound::stop },
                { "set_playing_offset", sound::set_playing_offset },
                { "get_playing_offset", sound::get_playing_offset },
                { NULL, NULL },
            };
            lua::add_lib(L, "sound", sound_lib);
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

        namespace sound {
            Container<sf::Sound>container = Container<sf::Sound>();

            int get(lua_State *L) {
                auto name = lua::get_string(L, -1);
                auto a = audio::SoundMap::request(name);
                sf::Sound *s = new sf::Sound(*a);
                container.add(s);
                lua_pushlightuserdata(L, s);
                return 1;
            }

            int release(lua_State *L) {
                auto s = (sf::Sound *)lua::get_lightuserdata(L, -1);
                container.remove(s);
                return 0;
            }

            int play(lua_State *L) {
                auto s = (sf::Sound *)lua::get_lightuserdata(L, -1);
                s->play();
                return 0;
            }

            int pause(lua_State *L) {
                auto s = (sf::Sound *)lua::get_lightuserdata(L, -1);
                s->pause();
                return 0;
            }

            int stop(lua_State *L) {
                auto s = (sf::Sound *)lua::get_lightuserdata(L, -1);
                s->stop();
                return 0;
            }

            int set_playing_offset(lua_State *L) {
                auto s = (sf::Sound *)lua::get_lightuserdata(L, -2);
                auto t = sf::milliseconds(lua::get_num(L, -1));
                s->setPlayingOffset(t);
                return 0;
            }

            int get_playing_offset(lua_State *L) {
                auto s = (sf::Sound *)lua::get_lightuserdata(L, -1);
                auto t = s->getPlayingOffset();
                lua_pushnumber(L, t.asMilliseconds());
                return 1;
            }

        };
    };
};
