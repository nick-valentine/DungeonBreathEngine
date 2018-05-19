#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <fstream>
#include <sstream>

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

	std::string get_name() const;

    TileType make_static(int key, sf::Vector2i pos, sf::Vector2i size_mod = sf::Vector2i(1,1));
    TileType make_dynamic(int key, std::vector<sf::Vector2i> pos, sf::Vector2i size_mod = sf::Vector2i(1,1));

    Tile *spawn(TileType t, sf::Vector2i loc);

    constexpr static int tile_size()
    {
        return BASE_TILE_SIZE * Tile::size();
    }
private:
	std::string name;
    sf::Texture *tex;
    int base_size;
    std::map<int, Tile*> tiles;
};

#endif // TILESET_H
