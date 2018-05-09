#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "WorldGenerator.h"
#include "TileSet.h"
#include "Input.h"
#include "Logger.h"

// plan for multiverse structure:
// Dimension is a container of Worlds
// World is a container of WorldChunks
// WorldChunk is a container of tiles
// World should be synonymous with level or room
class World
{
public:
    World(std::unique_ptr<TileSet> &&tile_set, std::unique_ptr<WorldGenerator> &&gen);
    ~World();

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);
private:
    static constexpr int world_height = 20;
    static constexpr int world_width = 20;
    std::unique_ptr<TileSet> tile_set;
    std::vector<Tile*> world;
};

#endif //WORLD_H
