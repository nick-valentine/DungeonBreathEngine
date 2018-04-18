#include "Tile.h"

Tile::Tile(sf::Rect<int> pos, sf::Vector2i sprite_pos)
{
    this->tex = TextureMap::request("./GameData/img/Overworld.png");
    this->sprite.setTexture(*tex);
    this->sprite.setTextureRect(
        sf::IntRect(
            sprite_pos.x * sprite_size,
            sprite_pos.y * sprite_size,
            sprite_size,
            sprite_size
        )
    );
    this->sprite.setPosition(pos.left, pos.top);
    this->sprite.setScale(pos.width, pos.height);
    this->rect = pos;
}

void Tile::update(int delta)
{

}

void Tile::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}
