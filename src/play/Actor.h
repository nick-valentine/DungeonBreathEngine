#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>

#include "core.h"
#include "script.h"
#include "render.h"

#include "ActorManager.h"

namespace play {
    class Actor;

    struct pain {
        int raw_dmg;
        sf::Vector2f force;
        Actor *attacker;
    };

    typedef std::shared_ptr<render::Tile> tile_ptr;

    class Actor
    {
    public:
        Actor(ActorManager *man, int handle, sf::Vector2i pos, sf::Vector2f scale, std::string name);
        virtual ~Actor();

        Actor(const Actor &other);

        void init();
        void update(int delta);
        void commit_update(int delta);
        void draw(sf::RenderWindow &window);
        void render(sf::RenderWindow &window);
        void hurt(pain p);
		void collide(Actor *a);

        std::string get_name() const;
        sf::FloatRect get_rect() const;
        void set_rect(sf::FloatRect& x);
        void set_location(sf::Vector2f x);

        sf::Vector2f get_velocity() const;
        void set_velocity(sf::Vector2f vel);

        void set_scale(sf::Vector2f scale);
        void set_origin(sf::Vector2f scale);

        void set_tileset(int i);

        tile_ptr get_tile();

        virtual Actor *clone();
    private:
        ActorManager *manager;
        int handle;
        sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
        sf::FloatRect rect;
        sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
        sf::Vector2f origin = sf::Vector2f(0.f, 0.f);

        render::TileSet *t = nullptr;
        tile_ptr current_tile = nullptr;

        std::vector<tile_ptr> tileset_cache = std::vector<tile_ptr>();

        std::string name;
        lua::Script *s;
    };
};

#endif // ACTOR_H
