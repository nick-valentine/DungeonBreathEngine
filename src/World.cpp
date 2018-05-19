#include "World.h"

World::World(std::unique_ptr<TileSet> &&tile_set, std::unique_ptr<WorldGenerator> &&gen)
{
    tile_set = std::move(tile_set);
    world = gen->generate(tile_set);
}

World::~World()
{
    for (size_t i = 0; i < world.size(); ++i) {
        delete world[i];
    }
}

void World::update(int delta, sf::RenderWindow &window)
{
    for (auto& value: world) {
        value->update(delta);
    }
}

void World::draw(sf::RenderWindow &window)
{
    for (auto& value: world) {
        value->draw(window);
    }
}
