#include "MusicManager.h"

namespace audio {
    std::vector<std::string> MusicManager::song_files = {
        "./GameData/sound/prepare_your_swords.ogg",
        "./GameData/sound/Harp.ogg",
        "./GameData/sound/little town - orchestral.ogg"
    };

    float MusicManager::volume = -1;
    MusicManager::Song MusicManager::now_playing = none;

    sf::Music MusicManager::music;

    void MusicManager::play(Song s)
    {
        if (s == now_playing) {
            return;
        }
        now_playing = s;
        if (volume == -1) {
            volume = core::ConfigLoader::get_int_option("volume", 100);
        }
        music.stop();
        if (!music.openFromFile(song_files[s])) {
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

    MusicManager::Song MusicManager::playing()
    {
        return now_playing;
    }

    void MusicManager::set_volume(float volume)
    {
        MusicManager::volume = volume;
        music.setVolume(volume);
    }
};
