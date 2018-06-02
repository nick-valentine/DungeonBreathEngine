#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <fstream>

#include "Container.h"

#include "ActorManager.h"
#include "WorldGenerator.h"
#include "TileSet.h"
#include "Input.h"
#include "Logger.h"

// plan for multiverse structure:
// Dimension is a container of Worlds
// World should be synonymous with level or room
class World
{
public:
    World(std::string tile_set, std::unique_ptr<WorldGenerator> &&gen);
    ~World();

    void set_tile(Tile *tile, int layer, sf::Vector2i pos);
    void remove_tile(int layer, sf::Vector2i pos);

    void add_actor(std::string name, sf::Vector2i pos);

    void save();
    void set_size(sf::Vector2i size);

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    void set_edit_mode(bool edit_mode);

    ActorManager::actor_ptr get_camera_target();
private:
    void add_layer(int num_layers = 1);

    bool update_actors =  true;
    static constexpr int world_height = 20;
    static constexpr int world_width = 20;
    std::unique_ptr<TileSet> tile_set;
    std::string name;
    std::string filename;
    std::string tileset;
    std::shared_ptr<ActorManager> actor_man;
    Dimension::Room world;

    sf::Vector2i size;
};

#endif //WORLD_H
