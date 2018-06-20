#ifndef SOUNDMAP_H
#define SOUNDMAP_H

#include <SFML/Audio.hpp>
#include <string>

#include "core.h"

namespace audio {
    sf::SoundBuffer instance(std::string file_name);
    typedef core::ResourceMap<sf::SoundBuffer, instance>SoundMap;
};


#endif // SOUNDMAP_H
