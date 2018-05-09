#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <string>
#include <fstream>
#include <sstream>

#include "Exceptions.h"
#include "TileSet.h"

class WorldGenerator
{
public:
    WorldGenerator() = default;;
    virtual ~WorldGenerator() = default;

    virtual std::vector<Tile*> generate(std::unique_ptr<TileSet> &tile_set) = 0;
private:
};

class WorldLoader : public WorldGenerator
{
public:
    WorldLoader(std::string file_name);
    virtual ~WorldLoader() = default;

    virtual std::vector<Tile*> generate(std::unique_ptr<TileSet> &tile_set);
private:
    std::string file_name;
};

#endif //WORLDGENERATOR_H
