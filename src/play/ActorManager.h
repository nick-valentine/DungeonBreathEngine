#ifndef ACTORMANAGER_H
#define ACTORMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include <memory>
#include <fstream>

#include "Macros.h"
#include "Exceptions.h"
#include "core.h"

namespace play {
    class Actor;

    struct Collision {
        int type;
        sf::FloatRect rect;
        std::shared_ptr<Actor> collider;
        std::shared_ptr<Actor> collidee;
    };

    typedef std::unique_ptr<Collision> collision_ptr;

    struct CType {
        int type;
        std::string action;
        std::string target;
        sf::Vector2i loc;
    };

    class ActorManager
    {
    public:
        typedef std::shared_ptr<Actor> actor_ptr;
        ActorManager();

        void update(int delta);
        void draw(sf::RenderWindow &window);
        int spawn(std::string name, sf::Vector2i pos);
        void add_collision_type(int type, std::string action, std::string target, sf::Vector2i loc = sf::Vector2i(0, 0));
        void add_collision_rect(int type, sf::FloatRect rect);
        void remove(int handle);
        void clear();
        void set_camera_target(int handle);
        void set_init_player_pos(sf::Vector2i pos);
        sf::Vector2i get_init_player_pos();
        actor_ptr get_camera_target();
        std::string get_actor_data() const;
        std::vector<Collision> get_collision_boxes() const;

        collision_ptr get_event();
        CType get_collision_type(int type);

        void set_player(int handle);
        actor_ptr get_player();
    private:
        bool check_available(std::string name);
        void check_collision(actor_ptr a);
        inline void resolve_collision(sf::FloatRect &a_rect, const sf::FloatRect &with, const sf::FloatRect &intersect);
        inline void trigger_event(actor_ptr a, Collision c, const sf::FloatRect &intersect);

        std::map<int, actor_ptr> actors;
        int max_id = 0;
        actor_ptr camera_target = nullptr;
        actor_ptr player = nullptr;

        collision_ptr event = nullptr;

        std::map<int, CType> collision_types;
        std::vector<Collision> collision_boxes;
        std::vector<std::string> available_actors;

        sf::Vector2i init_player_pos;
    };
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
