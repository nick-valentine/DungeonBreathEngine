#include "FontMap.h"

std::map<std::string, sf::Font> FontMap::font_map;

sf::Font *FontMap::request(std::string file_name)
{
    if (this->font_map.find(file_name) == font_map.end()) {
        sf::Font temp;
        if (!temp.loadFromFile(file_name)) {
            throw FileNotFoundException();
        }
        this->font_map[file_name] = temp;
        return &this->font_map[file_name];
    }
    return &this->font_map[file_name];
}

void FontMap::clear()
{
    font_map.clear();
}
