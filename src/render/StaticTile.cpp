#include "StaticTile.h"

namespace render {
    StaticTile::StaticTile(int key, sf::Sprite sprite) : Tile(), key(key)
    {
        this->sprite = sprite;
        this->sprite.setScale(Tile::scale, Tile::scale);
    }

    sf::Vector2i StaticTile::get_location()
    {
        auto v = this->sprite.getPosition();
        return sf::Vector2i(v.x, v.y);
    }

    void StaticTile::set_location(sf::Vector2i loc)
    {
        this->sprite.setPosition(loc.x, loc.y);
    }

    void StaticTile::play()
    {

    }

    void StaticTile::pause()
    {

    }

    void StaticTile::reset()
    {

    }

    int StaticTile::get_key()
    {
        return key;
    }

    sf::Vector2i StaticTile::get_size()
    {
        auto b = this->sprite.getLocalBounds();
        return sf::Vector2i(b.width, b.height) * Tile::size();
    }

    void StaticTile::set_scale(sf::Vector2f scale)
    {
        this->sprite.setScale(scale);
    }

    void StaticTile::set_origin(sf::Vector2f origin)
    {
        this->sprite.setOrigin(origin);
    }

    bool StaticTile::is_cacheable() const noexcept
    {
        return true;
    }

    sf::Sprite *StaticTile::get_icon()
    {
        return &sprite;
    }

    void StaticTile::update(int delta)
    {

    }

    void StaticTile::draw(sf::RenderTarget &window)
    {
        window.draw(this->sprite);
    }

    Tile *StaticTile::clone()
    {
        StaticTile *temp = new StaticTile(*this);
        return temp;
    }
};
