#ifndef SPRITESET_H
#define SPRITESET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace render {
    typedef int SpriteHandle;

    class SpriteSet
    {
    public:
        SpriteSet(sf::Texture *tex, int base_size = 16);
        ~SpriteSet();

        SpriteHandle make_sprite(sf::Vector2i pos, sf::Vector2i size_mod = sf::Vector2i(1,1));
        sf::Sprite *get_sprite(SpriteHandle name);
        void remove_sprite(sf::Sprite *s);

        size_t size();
    protected:
        int base_size;
        sf::Texture *tex;
        std::vector< std::shared_ptr<sf::Sprite> > sprites;
    };
};

#endif // SPRITESET_H
