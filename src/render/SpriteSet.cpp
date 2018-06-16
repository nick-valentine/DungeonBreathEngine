#include "SpriteSet.h"

namespace render {
    SpriteSet::SpriteSet(sf::Texture *tex, int base_size) :
        base_size(base_size), tex(tex)
    {
    }

    SpriteSet::~SpriteSet()
    {
    }

    SpriteHandle SpriteSet::make_sprite(sf::Vector2i pos, sf::Vector2i size_mod)
    {
        auto temp = new sf::Sprite();
        temp->setTexture(*tex);
        temp->setTextureRect(sf::IntRect(
            pos.x * base_size,
            pos.y * base_size,
            base_size * size_mod.x,
            base_size * size_mod.y
        ));
        this->sprites.push_back(
            std::shared_ptr<sf::Sprite>(temp)
        );
        return this->sprites.size() - 1;
    }

    sf::Sprite *SpriteSet::get_sprite(SpriteHandle handle)
    {
        return this->sprites[handle].get();
    }

    void SpriteSet::remove_sprite(sf::Sprite *s)
    {
        for (size_t i = 0; i < sprites.size(); ++i) {
            if (sprites[i].get() == s) {
                sprites[i].reset();
                if (sprites.size() > 0) {
                    sprites[i].swap(sprites[sprites.size() - 1]);
                }
                sprites.pop_back();
                return;
            }
        }
    }

    size_t SpriteSet::size()
    {
        return this->sprites.size();
    }
};
