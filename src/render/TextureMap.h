#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

#include <SFML/Graphics.hpp>
#include <string>

#include "core.h"

namespace render {
    sf::Texture instance(std::string file_name);
    typedef core::ResourceMap<sf::Texture, instance>TextureMap;
}

#endif // TEXTUREMAP_H
