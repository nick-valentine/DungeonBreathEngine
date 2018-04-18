#include "SpriteSet.h"

SpriteSet::SpriteSet(sf::Texture *tex, int base_size) :
    tex(tex), base_size(base_size)
{
}

SpriteHandle SpriteSet::make_sprite(sf::Vector2i pos, sf::Vector2i size_mod)
{
    sf::Sprite temp;
    temp.setTexture(*tex);
    temp.setTextureRect(sf::IntRect(
        pos.x * base_size * size_mod.x,
        pos.y * base_size * size_mod.y,
        base_size * size_mod.x,
        base_size * size_mod.y
    ));
    this->sprites.push_back(temp);
    return this->sprites.size() - 1;
}

sf::Sprite *SpriteSet::get_sprite(SpriteHandle handle)
{
    return &this->sprites[handle];
}

size_t SpriteSet::size()
{
    return this->sprites.size();
}
