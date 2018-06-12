#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>

#include "core.h"

namespace ui {
    enum InputMode {
        pad = 0,
        mouse,
    };

    class Element
    {
    public:
        Element(sf::IntRect pos);
        virtual ~Element() = default;

        virtual void update(int delta, sf::RenderWindow &window) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;

        virtual void set_pos(sf::IntRect pos);
        virtual sf::IntRect get_pos() const;
    private:
        sf::IntRect rect;
    };
};

#endif //ELEMENT_H
