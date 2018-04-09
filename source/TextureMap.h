#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

#include "Exceptions.h"

class TextureMap
{
public:
    TextureMap() = default;

    sf::Texture *request(std::string file_name);
    static void clear();
private:
    static std::map<std::string, sf::Texture> tex_map;
};

#endif // TEXTUREMAP_H
