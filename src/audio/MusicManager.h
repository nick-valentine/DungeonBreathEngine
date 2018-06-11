#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H
#include <iostream>

#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <vector>

#include "core.h"

namespace audio {
    class MusicManager
    {
    public:
        enum Song {
            none = 0,
            main_menu,
            playing_game
        };

        MusicManager() = delete;

        static void play(Song s);
        static void stop();

        Song playing();

        static void set_volume(float volume);

    private:
        static Song now_playing;
        static float volume;
        static sf::Music music;
        static std::vector<std::string> song_files;
    };
};

#endif // MUSICMANAGER_H
