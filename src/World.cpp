#include "World.h"

World::World(std::string tile_set, std::unique_ptr<WorldGenerator> &&gen)
{
    world = gen->generate(tile_set);
    name = gen->get_name();
    filename = gen->get_filename();
    tileset = tile_set;
    std::cout<<tile_set<<std::endl;
}

World::~World()
{
}

void World::set_tile(Tile *tile, int layer, sf::Vector2i pos)
{
    if (layer == 0 && pos.y >= 0 && pos.y < world[layer].size() &&
            pos.x >= 0 && pos.x < world[layer][pos.y].size()) {
        world[layer][pos.y][pos.x].reset(tile);
    }
}

void World::save()
{
    std::cout<<tileset<<std::endl;
    std::ofstream ofile(filename.c_str());
    ofile<<name<<"\n";
    ofile<<tileset<<"\n";

    for (auto &layer: world) {
        for (auto &line: layer) {
            for (auto &value: line) {
                if (value == nullptr) {
                    ofile<<-1<<" ";
                } else {
                    ofile<<value->get_key()<<" ";
                }
            }
            ofile<<"\n";
        }
        ofile<<"---\n";
    }

    ofile.close();
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
