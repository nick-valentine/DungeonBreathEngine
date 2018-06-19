#include "MusicManager.h"

namespace audio {
    float MusicManager::volume = -1;
    std::string MusicManager::now_playing = "";

    sf::Music MusicManager::music;

    void MusicManager::play(std::string name)
    {
        name = AUDIODIR + name;
        if (name == now_playing) {
            return;
        }
        now_playing = name;
        if (volume == -1) {
            volume = core::ConfigLoader::get_int_option("volume", 100);
        }
        music.stop();
        if (!music.openFromFile(name)) {
            throw core::FileNotFoundException();
        }
        music.setLoop(true);
        music.setVolume(volume);
        music.play();
    }

    void MusicManager::stop()
    {
        music.stop();
    }

    std::string MusicManager::playing()
    {
        return now_playing;
    }

    void MusicManager::set_volume(float volume)
    {
        MusicManager::volume = volume;
        music.setVolume(volume);
    }
};
