#ifndef FONTMAP_H
#define FONTMAP_H

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

#include "Exceptions.h"

class FontMap
{
public:
    FontMap() = default;

    sf::Font *request(std::string file_name);
    static void clear();
private:
    static std::map<std::string, sf::Font> font_map;
};

#endif // FONTMAP_H
