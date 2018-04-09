#include "TextureMap.h"

std::map<std::string, sf::Texture> TextureMap::tex_map;

sf::Texture *TextureMap::request(std::string file_name)
{

    if (this->tex_map.find(file_name) == tex_map.end()) {
        sf::Texture temp;
        if (!temp.loadFromFile(file_name)) {
            throw FileNotFoundException();
        }
        tex_map[file_name] = temp;
        return &tex_map[file_name];
    }
    return &tex_map[file_name];
}

void TextureMap::clear()
{
    tex_map.clear();
}
