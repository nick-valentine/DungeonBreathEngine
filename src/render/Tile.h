#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace render {
    class Tile
    {
    public:
        virtual sf::Vector2i get_location() = 0;
        virtual void set_location(sf::Vector2i loc) = 0;
        virtual ~Tile() = default;

        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void reset() = 0;

        virtual void update(int delta) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;

        virtual int get_key() = 0;
        virtual sf::Vector2i get_size() = 0;
        virtual void set_scale(sf::Vector2f scale) = 0;
        virtual void set_origin(sf::Vector2f scale) = 0;

        virtual sf::Sprite *get_icon() = 0;

        virtual Tile *clone() = 0;
        constexpr static int size()
        {
            return scale;
        }
    protected:
        constexpr static int scale = 4;
    };

};

#endif // TILE_H
