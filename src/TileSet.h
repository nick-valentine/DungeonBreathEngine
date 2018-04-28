#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "SpriteSet.h"

#define BASE_TILE_SIZE 16

typedef int TileType;

class Tile
{
public:
    Tile(sf::Sprite sprite, sf::Vector2i loc);

    void set_location(sf::Vector2i loc);

    void update(int delta);
    void draw(sf::RenderWindow &window);

    constexpr static int size()
    {
        return scale;
    }
private:
    constexpr static int scale = 4;
    sf::Sprite sprite;
};

class TileSet : protected SpriteSet
{
public:
    TileSet(sf::Texture *tex, int base_size = BASE_TILE_SIZE);

    TileType make(sf::Vector2i pos, sf::Vector2i size_mod = sf::Vector2i(1,1));

    Tile spawn(TileType t, sf::Vector2i loc);

    constexpr static int tile_size()
    {
        return BASE_TILE_SIZE * Tile::size();
    }
private:
};

#endif // TILESET_H
