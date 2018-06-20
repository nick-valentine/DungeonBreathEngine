#include "SoundMap.h"

namespace audio {
    sf::SoundBuffer instance(std::string file_name) {
        sf::SoundBuffer temp;
        if (!temp.loadFromFile(file_name)) {
            throw core::FileNotFoundException();
        }
        return temp;
    }
};
