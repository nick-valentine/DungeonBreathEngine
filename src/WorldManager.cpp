#include "WorldManager.h"

WorldManager::WorldManager()
{
    load("entry", sf::Vector2f(0, 0));
}

void WorldManager::update(int delta, sf::RenderWindow &window)
{
    current->update(delta, window);
}

void WorldManager::draw(sf::RenderWindow &window)
{
    current->draw(window);
}

void WorldManager::load(std::string name, sf::Vector2f player_coords)
{
    name = LEVELDIR + name + ".txt";
    current = world_ptr(new World("overworld", std::unique_ptr<WorldGenerator>(new WorldLoader(name))));
}

world_ptr WorldManager::get()
{
    return current;
}
