#include "Label.h"

Label::Label(sf::IntRect pos, sf::String contents)
{
    this->font = FontMap::request(DATADIR "font.unicode.ttf");
    this->text.setString(contents);
    this->text.setFont(*this->font);
    this->text.setCharacterSize(30);
    this->text.setFillColor(sf::Color::White);
    this->text.setOutlineColor(sf::Color::Blue);
    this->text.setPosition(float(pos.left), float(pos.top));
}

void Label::draw(sf::RenderWindow &window)
{
    window.draw(this->text);
}

void Label::set_position(sf::Vector2i pos)
{
    this->text.setPosition(float(pos.x), float(pos.y));
}

void Label::set_string(sf::String str)
{
    this->text.setString(str);
}

sf::String Label::get_string()
{
    return this->text.getString();
}

void Label::set_color(sf::Color col)
{
    this->text.setFillColor(col);
}

void Label::set_character_size(int size)
{
    this->text.setCharacterSize(size);
}
