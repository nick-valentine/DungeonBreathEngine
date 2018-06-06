#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include <memory>
#include <fstream>

#include "Macros.h"
#include "Exceptions.h"
#include "lua.h"
#include "Script.h"

class Actor;

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
    std::string get_actor_data() const;

    void set_player(int handle);
    actor_ptr get_player();
private:
    bool check_available(std::string name);
    void check_collision(actor_ptr a);
    inline void resolve_collision(sf::FloatRect &a_rect, const sf::FloatRect &with, const sf::FloatRect &intersect);

    std::map<int, actor_ptr> actors;
    int max_id = 0;
    actor_ptr camera_target = nullptr;
    actor_ptr player = nullptr;

    std::vector<sf::FloatRect> collision_boxes;
    std::vector<std::string> available_actors;
};


namespace lua {
    namespace actorman {
        void add(lua_State *L);
        int spawn(lua_State *L);
        int remove(lua_State *L);
        int clear(lua_State *L);
        int set_camera_target(lua_State *L);
        int get_camera_target(lua_State *L);
        int set_player(lua_State *L);
        int get_player(lua_State *L);
    };
};

#endif //ACTORMANAGER_H
