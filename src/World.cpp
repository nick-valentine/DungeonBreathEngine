#include "World.h"

World::World(std::string tile_set, std::unique_ptr<WorldGenerator> &&gen)
{
    world = gen->generate(tile_set);
    name = gen->get_name();
    filename = gen->get_filename();
    size = gen->get_size();
    actor_man = gen->get_actor_manager();
    tileset = tile_set;
}

World::~World()
{
}

void World::set_tile(Tile *tile, int layer, sf::Vector2i pos)
{
    if (layer < 0) {
        return;
    }
    if (layer >= world.size()) {
        add_layer((layer+1) - world.size());
    }
    if (pos.y >= 0 && pos.y < world[layer].size() &&
            pos.x >= 0 && pos.x < world[layer][pos.y].size()) {
        world[layer][pos.y][pos.x].reset(tile);
    }
}

void World::save()
{
    std::ofstream ofile(filename.c_str());
    ofile<<name<<"\n";
    ofile<<tileset<<"\n";
    ofile<<size.x<<" "<<size.y<<"\n";
    ofile<<"---\n";

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
    actor_man->update(delta);
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
    actor_man->draw(window);
}

ActorManager::actor_ptr World::get_camera_target()
{
    return this->actor_man->get_camera_target();
}

void World::add_layer(int num_layers)
{
    for (int n = 0; n < num_layers; ++n) {
        world.push_back(Dimension::Layer());
        auto idx = world.size() - 1;
        for (int i = 0; i < size.y; ++i) {
            world[idx].push_back(Dimension::Line());
            for (int j = 0; j < size.x; ++j) {
                world[idx][i].push_back(Dimension::TilePtr(nullptr));
            }
        }
    }
}
