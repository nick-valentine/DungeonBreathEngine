#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Element.h"

#include "Macros.h"
#include "core.h"

namespace ui {
    class Button : public Element
    {
    public:
        Button(sf::IntRect pos);
        virtual ~Button() = default;

        virtual void update(int delta, sf::RenderWindow &window);
        virtual void draw(sf::RenderWindow &window);

        virtual bool pressed();
        virtual bool neg_edge();

        virtual EReturn signal();

        virtual void set_hover(bool hover);
        virtual void set_pressed(bool pressed);
    protected:
        inline void update_pad_mode(int delta, sf::RenderWindow &window);
        inline void update_mouse_mode(int delta, sf::RenderWindow &window);
        bool was_pressed = false;
        bool last_pressed = false;
        bool is_hover = false;

#if DEBUG
        sf::RectangleShape debug_draw = sf::RectangleShape();
#endif //DEBUG
    };
};

#endif // BUTTON_H
