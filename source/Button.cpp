#include "Button.h"
#include "Exceptions.h"

Button::Button(sf::Rect<int> pos, std::string contents) : debug_draw(), font(), text(), rect(pos), was_pressed(false)
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
    this->text.setPosition(pos.left, pos.top);
}

void Button::update(int delta, sf::RenderWindow &window)
{
    this->was_pressed = false;
    if (this->rect.contains(sf::Mouse::getPosition(window)) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->was_pressed = true;
    }
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(this->debug_draw);
    window.draw(this->text);
}

bool Button::pressed()
{
    return this->was_pressed;
}
