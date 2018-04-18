#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "FontMap.h"

class Button
{
public:
    Button() = default;
    Button(sf::Rect<int> pos, std::string contents);
    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    bool pressed();
private:
    bool was_pressed;
    sf::Font *font;
    sf::Text text;
    sf::Rect<int> rect;

    sf::RectangleShape debug_draw;
};

#endif // BUTTON_H
