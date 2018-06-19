#include "SpriteButton.h"

namespace ui {
    SpriteButton::SpriteButton(
        sf::Rect<int> pos, 
        sf::Texture *tex,
        sf::IntRect normal,
        sf::IntRect hover,
        sf::IntRect press
    ) : Button(pos), tex(tex), 
        normal(*tex, normal),
        hover(*tex, hover),
        press(*tex, press)
    {
        this->normal.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
        this->hover.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
        this->press.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
    }

    void SpriteButton::draw(sf::RenderWindow &window)
    {
        if (this->was_pressed) {
            window.draw(this->press);
        } else if (this->is_hover) {
            window.draw(this->hover);
        } else {
            window.draw(this->normal);
        }
        Button::draw(window);
    }
};
