#include "ActorManager.h"

ActorManager::ActorManager()
{
    std::fstream ifile(SCRIPTDIR ACTORDIR "index.txt");
    std::string temp;
    ifile >> temp;
    while (ifile.good()) {
        available_actors.push_back(temp);
        ifile >> temp;
    }
    ifile.close();
}

void ActorManager::update(int delta)
{
    for (auto &i : actors) {
        i.second->update(delta);
    }
}

void ActorManager::draw(sf::RenderWindow &window)
{
    for (auto &i : actors) {
        i.second->draw(window);
    }
}

int ActorManager::spawn(std::string name, sf::Vector2i pos)
{
    if (!check_available(name)) {
        throw new UnavailableActorException();
    }
    std::string filename = ACTORDIR;
    filename += name;
    filename += ".lua";
    actor_ptr tmp(new Actor(pos, sf::Vector2f(1, 1), filename));
    actors[max_id] = tmp;
    max_id++;
    return max_id-1;
}

void ActorManager::remove(int handle)
{
    actors.erase(handle);
}

void ActorManager::clear()
{
    actors.clear();
}

void ActorManager::set_camera_target(int handle)
{
    this->camera_target = actors[handle];
}

ActorManager::actor_ptr ActorManager::get_camera_target()
{
    return this->camera_target;
}

bool ActorManager::check_available(std::string name)
{
    for (size_t i = 0; i < available_actors.size(); ++i) {
        app_container.get_logger()->info(available_actors[i].c_str());
        if (available_actors[i] == name) {
            return true;
        }
    }
    return false;
}
