#include "KeyButton.h"

namespace ui {
    KeyButton::KeyButton(sf::Rect<int> pos, sf::String contents) : Button(pos),
         label(sf::IntRect(pos.left, pos.top, pos.width, pos.height), contents)
    {
    }

    void KeyButton::draw(sf::RenderWindow &window)
    {
        if (this->was_pressed) {
            label.set_color(sf::Color::Red);
        }
        else if (this->is_hover) {
            label.set_color(sf::Color::Yellow);
        }
        else {
            label.set_color(sf::Color::White);
        }
        label.draw(window);
        Button::draw(window);
    }

    void KeyButton::set_label(sf::String contents)
    {
        label.set_string(contents);
    }

    sf::String KeyButton::get_label() 
    {
        return label.get_string();
    }
};
