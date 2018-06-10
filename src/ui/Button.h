#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "core.h"

class Button
{
public:
    Button(sf::IntRect pos);
    virtual ~Button() = default;

    virtual void update(int delta, Input *input, sf::RenderWindow &window);
    virtual void draw(sf::RenderWindow &window);

    virtual bool pressed();
    virtual bool neg_edge();
    virtual void set_hover(bool hover);
    virtual void reset_hover_override();
    virtual void set_pressed(bool pressed);
protected:
    bool was_pressed;
    bool last_pressed;
    bool is_hover;
    bool is_override_hover;
    sf::Rect<int> rect;

    sf::RectangleShape debug_draw;
};

#endif // BUTTON_H
