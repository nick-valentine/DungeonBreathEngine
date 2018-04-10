#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H
#include <iostream>

#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <vector>

#include "Exceptions.h"

class MusicManager
{
public:
    enum Song {
        main_menu = 0,
        playing_game = 1,
    };

    MusicManager() = delete;

    static void play(Song s);
    static void stop();

private:
    static sf::Music music;
    static std::vector<std::string> song_files;
};

#endif // MUSICMANAGER_H
