#include "World.h"

#define LAYERS_UNDER_ACTOR 5

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

void World::remove_tile(int layer, sf::Vector2i pos)
{
    if (layer >= 0 && layer < world.size() &&
        pos.y >= 0 && pos.y < world[layer].size() &&
        pos.x >= 0 && pos.x < world[layer][pos.y].size()
    ) {
        world[layer][pos.y][pos.x].reset(nullptr);
    }
}

void World::add_actor(std::string name, sf::Vector2i pos)
{
    this->actor_man->spawn(name, pos);
}

void World::add_collision(int type, sf::Vector2i pos)
{
    actor_man->add_collision_rect(type, sf::FloatRect(pos.x, pos.y, TileSet::tile_size(), TileSet::tile_size()));
}

void World::save()
{
    std::ofstream ofile(filename.c_str());
    ofile<<name<<"\n";
    ofile<<tileset<<"\n";
    ofile<<size.x<<" "<<size.y<<"\n";
    ofile<<"---\n";
    ofile<<actor_man->get_actor_data();
    ofile<<"---\n";
    ofile<<convert_collision_boxes();
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
    if (update_actors) {
        actor_man->update(delta);
    }
}

void World::draw(sf::RenderWindow &window)
{
    for (size_t i = 0; i < LAYERS_UNDER_ACTOR && i < world.size(); ++i) {
        auto & layer = world[i];
        for (auto& line: layer) {
            for (auto& value: line) {
                if (value != nullptr) {
                    value->draw(window);
                }
            }
        }
    }

    actor_man->draw(window);

    for (size_t i = LAYERS_UNDER_ACTOR; i < world.size(); ++i) {
        auto & layer = world[i];
        for (auto& line: layer) {
            for (auto& value: line) {
                if (value != nullptr) {
                    value->draw(window);
                }
            }
        }
    }
}

void World::set_edit_mode(bool edit_mode)
{
    this->update_actors = !edit_mode;
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

std::string World::convert_collision_boxes()
{
    std::stringstream ss;
    auto boxes = actor_man->get_collision_boxes();
    for (int i = 0; i < size.y; ++i) {
        for (int j = 0; j < size.x; ++j) {
            auto point = sf::Vector2f(j*TileSet::tile_size(), i*TileSet::tile_size());
            auto type = 0;
            for (const auto &i : boxes) {
                if (i.rect.contains(point)) {
                    type = i.type;
                    break;
                }
            }
            ss<<type<<" ";
        }
        ss<<"\n";
    }
    return ss.str();
}
