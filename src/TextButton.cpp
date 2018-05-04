#include "TextButton.h"

TextButton::TextButton(sf::Rect<int> pos, sf::String contents) : Button(pos),
	 font(), text(), background(TextureMap::request("./GameData/img/RPG_GUI_v1.png"))
{

    this->font = FontMap::request("./GameData/font.unicode.ttf");
    this->text.setString(contents);
    this->text.setFont(*this->font);
    this->text.setCharacterSize(30);
    this->text.setFillColor(sf::Color::White);
    this->text.setOutlineColor(sf::Color::Blue);
    this->text.setPosition(float(pos.left) + 50.0f, float(pos.top));

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
    window.draw(this->text);
    Button::draw(window);
}

