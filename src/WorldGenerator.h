#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <string>
#include <fstream>
#include <sstream>

#include "Exceptions.h"
#include "TileSet.h"

namespace Dimension {
    typedef std::unique_ptr<Tile> TilePtr;
    typedef std::vector<TilePtr> Line;
    typedef std::vector<Line> Layer;
    typedef std::vector<Layer> Room;
}

class WorldGenerator
{
public:
    WorldGenerator() = default;;
    virtual ~WorldGenerator() = default;

    virtual Dimension::Room generate(std::string tile_set) = 0;
    virtual std::string get_name() = 0;
    virtual std::string get_filename() = 0;
    virtual std::string get_tileset() = 0;
    virtual sf::Vector2i get_size() = 0;
private:
};

class WorldLoader : public WorldGenerator
{
public:
    WorldLoader(std::string file_name);
    virtual ~WorldLoader() = default;

    virtual Dimension::Room generate(std::string tile_set);
    virtual std::string get_name();
    virtual std::string get_filename();
    virtual std::string get_tileset();
    virtual sf::Vector2i get_size();
private:
    Dimension::Layer spawn_layer(std::ifstream &ifile, TileSet &tile_set);
    Dimension::Line spawn_line(std::string &line, int line_number, TileSet &tile_set);
    std::string file_name;
    std::string tile_set;
    sf::Vector2i size;
};

#endif //WORLDGENERATOR_H
