#ifndef SPRITESET_H
#define SPRITESET_H

#include <SFML/Graphics.hpp>

typedef int SpriteHandle;

class SpriteSet
{
public:
    SpriteSet(sf::Texture *tex, int base_size = 16);

    SpriteHandle make_sprite(sf::Vector2i pos, sf::Vector2i size_mod = sf::Vector2i(1,1));
    sf::Sprite *get_sprite(SpriteHandle name);

    size_t size();
protected:
    int base_size;
    sf::Texture *tex;
    std::vector<sf::Sprite> sprites;
};

#endif // SPRITESET_H
