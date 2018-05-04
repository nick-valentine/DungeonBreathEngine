#include "Button.h"
#include "Exceptions.h"

Button::Button(sf::IntRect pos) : 
    was_pressed(false),
    is_hover(false),
    is_override_hover(false),
    rect(pos), 
    debug_draw()
{
    this->debug_draw = sf::RectangleShape();
    this->debug_draw.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
    this->debug_draw.setSize(sf::Vector2f(float(pos.width), float(pos.height)));
    this->debug_draw.setOutlineColor(sf::Color::Blue);
    this->debug_draw.setOutlineThickness(1);
    this->debug_draw.setFillColor(sf::Color::Transparent);
}

void Button::update(int delta, Input *input, sf::RenderWindow &window)
{
    this->was_pressed = false;
	if (this->rect.contains(sf::Mouse::getPosition(window)) || (this->is_override_hover && this->is_hover)) {
		this->is_hover = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || input->is_key_pressed(Input::accept)) {
			this->was_pressed = true;
		}
	}
	else {
		this->is_hover = false;
	}
}

void Button::draw(sf::RenderWindow &window)
{

	if (this->was_pressed) {
        this->debug_draw.setOutlineColor(sf::Color::Blue);
	} else if (this->is_hover) {
        this->debug_draw.setOutlineColor(sf::Color::Green);
	} else {
        this->debug_draw.setOutlineColor(sf::Color::White);
	}
    window.draw(this->debug_draw);
}

bool Button::pressed()
{
    return this->was_pressed;
}

void Button::set_hover(bool hover)
{
	this->is_hover = hover;
	this->is_override_hover = true;
}

void Button::reset_hover_override()
{
	this->is_override_hover = false;
}

void Button::set_pressed(bool pressed)
{
	this->was_pressed = pressed;
}
