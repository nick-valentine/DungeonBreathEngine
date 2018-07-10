#include "DynamicTile.h"

namespace render {
    DynamicTile::DynamicTile(int key, sf::Texture *tex, sf::Vector2i size_mod, int anim_speed, int base_size) : 
        Tile(), anim(tex, anim_speed, base_size), loc(sf::Vector2i(0,0)), size_mod(size_mod), key(key)
    {

    }

    void DynamicTile::add_frame(sf::IntRect pos)
    {
        anim.add_sprite(pos);
    }

    sf::Vector2i DynamicTile::get_location()
    {
        return this->loc;
    }

    void DynamicTile::set_location(sf::Vector2i loc)
    {
        this->loc = loc;
    }

    void DynamicTile::play()
    {
        anim.play();
    }

    void DynamicTile::pause()
    {
        anim.pause();
    }

    void DynamicTile::reset()
    {
        anim.reset();
    }

    int DynamicTile::get_key()
    {
        return key;
    }

    sf::Vector2i DynamicTile::get_size()
    {
        return this->size_mod * BASE_TILE_SIZE * Tile::size();
    }

    void DynamicTile::set_scale(sf::Vector2f scale)
    {
        this->scale = scale;
    }

    void DynamicTile::set_origin(sf::Vector2f origin)
    {
        anim.set_origin(origin);
    }

    bool DynamicTile::is_cacheable() const noexcept
    {
        return false;
    }

    sf::Sprite *DynamicTile::get_icon()
    {
        return anim.get_icon();
    }

    void DynamicTile::update(int delta)
    {
        anim.update(delta);
    }

    void DynamicTile::draw(sf::RenderTarget &window)
    {
        anim.draw(window, sf::FloatRect(loc.x, loc.y, Tile::size() * scale.x, Tile::size() * scale.y));
    }

    Tile *DynamicTile::clone()
    {
        DynamicTile *temp = new DynamicTile(*this);
        return temp;
    }
};
