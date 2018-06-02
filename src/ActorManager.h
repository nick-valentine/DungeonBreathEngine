#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <map>
#include <memory>
#include <fstream>

#include "Exceptions.h"
#include "Actor.h"

class ActorManager
{
public:
    typedef std::shared_ptr<Actor> actor_ptr;
    ActorManager();

    void update(int delta);
    void draw(sf::RenderWindow &window);
    int spawn(std::string name, sf::Vector2i pos);
    void remove(int handle);
    void clear();
    void set_camera_target(int handle);
    actor_ptr get_camera_target();
private:
    bool check_available(std::string name);

    std::map<int, actor_ptr> actors;
    int max_id = 0;
    actor_ptr camera_target;

    std::vector<std::string> available_actors;
};

#endif //ACTORMANAGER_H
