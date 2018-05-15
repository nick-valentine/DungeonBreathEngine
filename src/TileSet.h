#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

#include "Macros.h"
#include "TextureMap.h"
#include "SpriteSet.h"
#include "Animation.h"

#define BASE_TILE_SIZE 16

typedef int TileType;

class Tile
{
public:
    virtual void set_location(sf::Vector2i loc) = 0;
    virtual ~Tile() = default;

    virtual void update(int delta) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    virtual Tile *clone() = 0;
    constexpr static int size()
    {
        return scale;
    }
protected:
    constexpr static int scale = 4;
};

class DynamicTile : public Tile
{
public:
    DynamicTile(sf::Texture *tex, sf::Vector2i size_mod = sf::Vector2i(1,1));
    void add_frame(sf::IntRect pos);

    void set_location(sf::Vector2i loc);

    void update(int delta);
    void draw(sf::RenderWindow &window);

    Tile *clone();
private:
    Animation anim;
    sf::Vector2i loc;
    sf::Vector2i size_mod;
};

class StaticTile : public Tile
{
public:
    StaticTile(sf::Sprite sprite);

    void set_location(sf::Vector2i loc);

    void update(int delta);
    void draw(sf::RenderWindow &window);

    Tile *clone();
private:
    sf::Sprite sprite;
};

class TileSet 
{
public:
    TileSet(std::string def_file);
    TileSet(sf::Texture *tex, int base_size = BASE_TILE_SIZE);
    ~TileSet();

    TileSet(const TileSet &other) = delete;
    TileSet operator=(const TileSet &other) = delete;
    TileSet(const TileSet &&other) = delete;
    TileSet operator=(const TileSet &&other) = delete;

    TileType make_static(sf::Vector2i pos, sf::Vector2i size_mod = sf::Vector2i(1,1));
    TileType make_dynamic(std::vector<sf::Vector2i> pos, sf::Vector2i size_mod = sf::Vector2i(1,1));

    Tile *spawn(TileType t, sf::Vector2i loc);

    constexpr static int tile_size()
    {
        return BASE_TILE_SIZE * Tile::size();
    }
private:
    sf::Texture *tex;
    int base_size;
    std::vector<Tile*> tiles;
};

namespace TileSets {
    enum Overworld {
        grass_thick = 0,
        grass_to_thick_tl,
        grass_to_thick_tr,
        grass_to_thick_bl,
        grass_to_thick_br,
        thick_to_grass_tl,
        thick_to_grass_tr,
        thick_to_grass_bl,
        thick_to_grass_br,
        thick_to_water_tl,
        thick_to_water_tr,
        thick_to_water_bl,
        thick_to_water_br,
        thick_to_water_t,
        thick_to_water_l,
        thick_to_water_r,
        thick_to_water_b,
        water_to_thick_tl,
        water_to_thick_tr,
        water_to_thick_bl,
        water_to_thick_br,
        stone,
        wave,
        water_circle_1,
    };

    std::unique_ptr<TileSet> overworld();
};


#endif // TILESET_H
