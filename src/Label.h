#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include "FontMap.h"

class Label
{
public:
    Label(sf::IntRect pos, sf::String contents);

    void draw(sf::RenderWindow &window);

    void set_string(sf::String str);
private:
    sf::Font *font;
    sf::Text text;
};

#endif //LABEL_H
