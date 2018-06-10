#ifndef TILESET_H
#define TILESET_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>

#include "core.h"
#include "TextureMap.h"
#include "render/Macros.h"
#include "Tile.h"
#include "StaticTile.h"
#include "DynamicTile.h"

namespace render {

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
        TileType make_dynamic(int key, std::vector<sf::Vector2i> pos, sf::Vector2i size_mod = sf::Vector2i(1,1), int anim_speed = 1);

        Tile *spawn(TileType t, sf::Vector2i loc);

        std::vector<int> get_keys() const;

        constexpr static int tile_size()
        {
            return BASE_TILE_SIZE * Tile::size();
        }
    private:
        std::string name;
        sf::Texture *tex;
        int base_size;
        int anim_speed;
        std::map<int, std::unique_ptr<Tile> > tiles;
    };
}

#endif // TILESET_H
