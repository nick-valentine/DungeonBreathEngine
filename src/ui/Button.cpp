#include "Button.h"

namespace ui {
    Button::Button(sf::IntRect pos) : Element(pos) 
    {
#if DEBUG
        this->debug_draw = sf::RectangleShape();
        this->debug_draw.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
        this->debug_draw.setSize(sf::Vector2f(float(pos.width), float(pos.height)));
        this->debug_draw.setOutlineColor(sf::Color::Blue);
        this->debug_draw.setOutlineThickness(1);
        this->debug_draw.setFillColor(sf::Color::Transparent);
#endif //DEBUG
    }

    void Button::update(int delta, sf::RenderWindow &window)
    {
        this->last_pressed = this->was_pressed;
        this->was_pressed = false;
        switch (this->get_mode()) {
        case InputMode::pad:
            return update_pad_mode(delta, window);
        case InputMode::mouse:
            return update_mouse_mode(delta, window);
        }
    }

    void Button::draw(sf::RenderWindow &window)
    {
#if DEBUG
        if (this->was_pressed) {
            this->debug_draw.setOutlineColor(sf::Color::Blue);
        } else if (this->is_hover) {
            this->debug_draw.setOutlineColor(sf::Color::Green);
        } else {
            this->debug_draw.setOutlineColor(sf::Color::White);
        }
        window.draw(this->debug_draw);
#endif //DEBUG
    }

    bool Button::pressed()
    {
        return this->was_pressed;
    }

    bool Button::neg_edge()
    {
        return (this->last_pressed && !this->was_pressed);
    }

    EReturn Button::signal()
    {
        EReturn r;
        r.type = EType::NONE;
        r.iVal = 0;
        if (neg_edge()) {
            r.type = EType::INT;
            r.iVal = 1;
        }
        return r;
    }

    void Button::set_hover(bool hover)
    {
        this->is_hover = hover;
    }

    void Button::set_pressed(bool pressed)
    {
        this->was_pressed = pressed;
    }

    void Button::update_pad_mode(int delta, sf::RenderWindow &window)
    {
        auto input = core::app_container.get_input();
        if (this->is_hover && input->is_key_pressed(core::Input::accept)) {
            this->was_pressed = true;
        }
    }

    void Button::update_mouse_mode(int delta, sf::RenderWindow &window)
    {
        auto input = core::app_container.get_input();
        auto rect = this->get_pos();

        this->is_hover = false;
        if (rect.contains(sf::Mouse::getPosition(window))) {
            this->is_hover = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->was_pressed = true;
            }
        } 
    }
};
