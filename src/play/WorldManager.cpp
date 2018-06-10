#include "WorldManager.h"

namespace play {
    WorldManager::WorldManager()
    {
        load("entry", sf::Vector2i(0, 0));
    }

    void WorldManager::update(int delta, sf::RenderWindow &window)
    {
        current->update(delta, window);
        if (current->status() == World::change) {
            load(current->next_level(), current->next_player_pos());
        }
    }

    void WorldManager::draw(sf::RenderWindow &window)
    {
        current->draw(window);
    }

    void WorldManager::load(std::string name, sf::Vector2i player_coords)
    {
        name = LEVELDIR + name + ".txt";
        current.reset(new World("overworld", std::unique_ptr<WorldGenerator>(new WorldLoader(name))));
        current->set_init_player_pos(player_coords);
    }

    world_ptr WorldManager::get()
    {
        return current;
    }
}
