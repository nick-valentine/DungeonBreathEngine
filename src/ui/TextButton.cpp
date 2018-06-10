#include "TextButton.h"

namespace ui {
    TextButton::TextButton(sf::Rect<int> pos, sf::String contents) : Button(pos),
         label(sf::IntRect(pos.left+50.0f, pos.top, pos.width, pos.height), contents), background(render::TextureMap::request("./GameData/img/RPG_GUI_v1.png"))
    {
        this->back = sf::Sprite(*background, sf::IntRect(0, 128, 300, 57));
        this->back.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
        this->back_hover = sf::Sprite(*background, sf::IntRect(0, 285, 300, 57));
        this->back_hover.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
        this->back_press = sf::Sprite(*background, sf::IntRect(0, 360, 300, 57));
        this->back_press.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
    }

    void TextButton::draw(sf::RenderWindow &window)
    {
        if (this->was_pressed) {
            window.draw(this->back_press);
        }
        else if (this->is_hover) {
            window.draw(this->back_hover);
        }
        else {
            window.draw(this->back);
        }
        label.draw(window);
        Button::draw(window);
    }

    sf::String TextButton::get_label()
    {
        return label.get_string();
    }

    void TextButton::set_label(sf::String contents)
    {
        label.set_string(contents);
    }
};
