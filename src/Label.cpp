#include "Label.h"

Label::Label(sf::IntRect pos, sf::String contents)
{
    this->font = FontMap::request("./GameData/font.unicode.ttf");
    this->text.setString(contents);
    this->text.setFont(*this->font);
    this->text.setCharacterSize(30);
    this->text.setFillColor(sf::Color::White);
    this->text.setOutlineColor(sf::Color::Blue);
    this->text.setPosition(float(pos.left) + 50.0f, float(pos.top));
}

void Label::draw(sf::RenderWindow &window)
{
    window.draw(this->text);
}

void Label::setString(sf::String str)
{
    this->text.setString(str);
}
