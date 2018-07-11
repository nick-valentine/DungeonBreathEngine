#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>

#include "Element.h"

#include "render.h"

namespace ui {
    class Label : public Element
    {
    public:
        Label(sf::IntRect pos, sf::String contents);

        void draw(sf::RenderTarget &window);
        void update(int delta, sf::RenderWindow &window);

        void set_string(sf::String str);
        sf::String get_string();
        void set_color(sf::Color col);
        void set_character_size(int size);

        void set_pos(sf::IntRect pos);
    private:
        sf::Font *font;
        sf::Text text;
    };
};

#endif //LABEL_H
