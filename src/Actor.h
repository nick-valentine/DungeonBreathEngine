#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>

#include "Container.h"

#include "TextureMap.h"
#include "TileSet.h"

#include "lua.h"
#include "Script.h"

class Actor;

struct pain {
    int raw_dmg;
    sf::Vector2f force;
    Actor *attacker;
};

typedef std::shared_ptr<Tile> tile_ptr;

class Actor
{
public:
    Actor(sf::Vector2i pos, sf::Vector2i scale);
    virtual ~Actor();

    Actor(const Actor &other);

    virtual void update(int delta);
    virtual void draw(sf::RenderWindow &window);
    virtual void hurt(pain p);

    sf::Rect<int> get_rect() const;
    void set_rect(sf::Rect<int>& x);

    sf::Vector2f get_velocity() const;
    void set_velocity(sf::Vector2f vel);

    void set_tileset(int i);

    tile_ptr get_tile();

    virtual Actor *clone();
private:
    sf::Vector2f velocity;
    sf::Rect<int> rect;

    TileSet *t;
    tile_ptr current_tile;
    Input *input;
    Logger *logger;

    std::vector<tile_ptr> tileset_cache;

     Script s;
};

namespace lua {
    namespace actor {
        void add(lua_State *L);
        int get_rect(lua_State *L);
        int get_velocity(lua_State *L);
        int set_velocity(lua_State *L);
        int set_tileset(lua_State *L);
        int pause_anim(lua_State *L);
        int play_anim(lua_State *L);
        int reset_anim(lua_State *L);
    };
};

#endif // ACTOR_H
