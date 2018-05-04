#include "SpriteButton.h"

SpriteButton::SpriteButton(
    sf::Rect<int> pos, 
    sf::Texture *tex,
    sf::IntRect normal,
    sf::IntRect hover,
    sf::IntRect press
) : Button(pos), tex(tex), 
    normal(*tex, normal),
    hover(*tex, hover),
    press(*tex, press)
{
    this->normal.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
    this->hover.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
    this->press.setPosition(sf::Vector2f(float(pos.left), float(pos.top)));
}

void SpriteButton::draw(sf::RenderWindow &window)
{
	if (this->was_pressed) {
		window.draw(this->press);
	} else if (this->is_hover) {
		window.draw(this->hover);
	} else {
		window.draw(this->normal);
	}
    Button::draw(window);
}

SpriteButton ui::left(sf::IntRect pos)
{
    return SpriteButton(
        pos,
        TextureMap::request("./GameData/img/RPG_GUI_v1.png"),
        sf::IntRect(320, 60, 40, 40),
        sf::IntRect(320, 110, 40, 40),
        sf::IntRect(320, 10, 40, 40)
    );
}

SpriteButton ui::right(sf::IntRect pos)
{
    return SpriteButton(
        pos,
        TextureMap::request("./GameData/img/RPG_GUI_v1.png"),
        sf::IntRect(360, 60, 50, 50),
        sf::IntRect(360, 110, 50, 50),
        sf::IntRect(360, 10, 50, 50)
    );
}
