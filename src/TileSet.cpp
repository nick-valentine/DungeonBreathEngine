#include "TileSet.h"

Tile::Tile(sf::Sprite sprite, sf::Vector2i loc)
{
    this->sprite = sprite;
    this->sprite.setPosition(loc.x, loc.y);
    this->sprite.setScale(scale, scale);
}

void Tile::update(int delta)
{

}

void Tile::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}

TileSet::TileSet(sf::Texture *tex, int base_size) : SpriteSet(tex,base_size)
{
}

TileType TileSet::make(sf::Vector2i pos, sf::Vector2i size_mod)
{
    return TileType(make_sprite(pos, size_mod));
}

Tile TileSet::spawn(TileType t, sf::Vector2i loc)
{
    auto spr = get_sprite(SpriteHandle(t));
    return Tile(*spr, loc);
}
