#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class TextureMap
{
public:
    TextureMap();
    ~TextureMap();

    sf::Texture *request(std::string fileName);
    static void clear();
private:
    static std::map<std::string, sf::Texture> texMap;
};

#endif // TEXTUREMAP_H
