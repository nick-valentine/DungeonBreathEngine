#include "../headers/TextureMap.h"

std::map<std::string, sf::Texture> TextureMap::texMap;

TextureMap::TextureMap()
{

}

TextureMap::~TextureMap()
{

}

sf::Texture *TextureMap::request(std::string fileName)
{
    if (this->texMap.find(fileName) == texMap.end()) {
        //texture not found in map, load from file
        sf::Texture temp;
        if (!temp.loadFromFile(fileName)) {
            //texture could not be loaded
            exit(1);
        } else {
            //texture loaded, add to map and return it
            texMap[fileName] = temp;
            return &texMap[fileName];
        }
    } else {
        //texture already loaded
        return &texMap[fileName];
    }
}

void TextureMap::clear()
{
    texMap.clear();
}
