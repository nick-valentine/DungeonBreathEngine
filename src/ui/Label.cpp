#include "Label.h"

namespace ui {
    Label::Label(sf::IntRect pos, sf::String contents) : Element(pos)
    {
        this->font = render::FontMap::request(DATADIR "font.unicode.ttf");
        this->text.setString(contents);
        this->text.setFont(*this->font);
        this->text.setCharacterSize(30);
        this->text.setFillColor(sf::Color::White);
        this->text.setOutlineColor(sf::Color::Blue);
        this->text.setPosition(float(pos.left), float(pos.top));
    }

    void Label::draw(sf::RenderTarget &window)
    {
        window.draw(this->text);
    }

    void Label::update(int delta, sf::RenderWindow &window)
    {

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

    void Label::set_pos(sf::IntRect pos)
    {
        this->text.setPosition(pos.left, pos.top);
        Element::set_pos(pos);
    }
};
