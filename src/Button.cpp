#include "Button.h"
#include "Exceptions.h"

Button::Button(sf::Rect<int> pos, std::string contents) : 
	debug_draw(), font(), text(), rect(pos), was_pressed(false),
	background(TextureMap::request("./GameData/img/RPG_GUI_v1.png"))
{
    this->debug_draw = sf::RectangleShape();
    this->debug_draw.setPosition(sf::Vector2f(pos.left, pos.top));
    this->debug_draw.setSize(sf::Vector2f(pos.width, pos.height));
    this->debug_draw.setOutlineColor(sf::Color::Blue);
    this->debug_draw.setOutlineThickness(1);
    this->debug_draw.setFillColor(sf::Color::Transparent);

    this->font = FontMap::request("./GameData/font.ttf");
    this->text.setString(contents);
    this->text.setFont(*this->font);
    this->text.setCharacterSize(30);
    this->text.setFillColor(sf::Color::White);
    this->text.setOutlineColor(sf::Color::Blue);
    this->text.setPosition(pos.left + 50, pos.top);

	this->back = sf::Sprite(*background, sf::IntRect(0, 128, 300, 57));
	this->back.setPosition(sf::Vector2f(pos.left, pos.top));
	this->back_hover = sf::Sprite(*background, sf::IntRect(0, 285, 300, 57));
	this->back_hover.setPosition(sf::Vector2f(pos.left, pos.top));
	this->back_press = sf::Sprite(*background, sf::IntRect(0, 360, 300, 57));
	this->back_press.setPosition(sf::Vector2f(pos.left, pos.top));
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
		window.draw(this->back_press);
	}
	else if (this->is_hover) {
		window.draw(this->back_hover);
	}
	else {
		window.draw(this->back);
	}
    window.draw(this->debug_draw);
    window.draw(this->text);
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