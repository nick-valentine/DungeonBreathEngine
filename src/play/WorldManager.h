#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "World.h"

namespace play {
    typedef std::shared_ptr<World> world_ptr;

    class WorldManager
    {
    public:
        WorldManager();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        void load(std::string name, sf::Vector2i player_coords);

        world_ptr get();
    private:
        world_ptr current;
    };
};

#endif //WORLDMANAGER_H
