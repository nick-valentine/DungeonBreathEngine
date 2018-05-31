#include "World.h"

World::World(std::unique_ptr<TileSet> &&tile_set, std::unique_ptr<WorldGenerator> &&gen)
{
    tile_set = std::move(tile_set);
    world = gen->generate(tile_set);
}

World::~World()
{
}

void World::set_tile(Tile *tile, int layer, sf::Vector2i pos)
{
    world[layer][pos.y][pos.x].reset(tile);
}

void World::update(int delta, sf::RenderWindow &window)
{
    for (auto& layer: world) {
        for (auto& line: layer) {
            for (auto& value: line) {
                if (value != nullptr) {
                    value->update(delta);
                }
            }
        }
    }
}

void World::draw(sf::RenderWindow &window)
{
    for (auto& layer: world) {
        for (auto& line: layer) {
            for (auto& value: line) {
                if (value != nullptr) {
                    value->draw(window);
                }
            }
        }
    }
}
