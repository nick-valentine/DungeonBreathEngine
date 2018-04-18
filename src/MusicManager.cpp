#include "MusicManager.h"

std::vector<std::string> MusicManager::song_files = {
    "./GameData/sound/prepare_your_swords.ogg",
    "./GameData/sound/Harp.ogg",
    "./GameData/sound/little town - orchestral.ogg"
};

sf::Music MusicManager::music;

void MusicManager::play(Song s)
{
    music.stop();
    if (!music.openFromFile(song_files[s])) {
        throw FileNotFoundException();
    }
    music.setLoop(true);
    music.play();
}

void MusicManager::stop()
{
    music.stop();
}
