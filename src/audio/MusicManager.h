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
        MusicManager() = delete;

		static void init();
		static void close();
		
        static void play(std::string name);
        static void stop();

        static std::string playing();

        static void set_volume(float volume);
    private:
        static std::string now_playing;
        static float volume;
        static sf::Music *music;
        static std::vector<std::string> song_files;
    };
};

#endif // MUSICMANAGER_H
