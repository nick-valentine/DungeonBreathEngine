#include "Actor.h"

#define TABLENAME "me"

namespace play {
    Actor::Actor(ActorManager *man, int handle, sf::Vector2i pos, sf::Vector2f scale, std::string name) : manager(man), name(name)
    {
        this->handle = handle;
        this->rect = sf::FloatRect(pos.x, pos.y, scale.x, scale.y);
        this->velocity = sf::Vector2f(0, 0);

        std::string filename = ACTORDIR;
        filename += name;
        filename += ".lua";
        s = new lua::Script(filename);
        s->call();

        lua_getglobal(s->s, TABLENAME);
        auto me_table = lua_gettop(s->s);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, TABLENAME " table not found");
        }
        auto tileset = s->get_field("tileset");
        lua_pushlightuserdata(s->s, this);
        lua_setfield(s->s, me_table, "self");
        lua_pushnumber(s->s, this->handle);
        lua_setfield(s->s, me_table, "handle");
        lua_pushlightuserdata(s->s, man);
        lua_setfield(s->s, me_table, "manager");

        t = new render::TileSet(tileset);
        tileset_cache.push_back(tile_ptr(t->spawn(0, pos)));
        current_tile = tileset_cache[0];
    }

    Actor::~Actor()
    {
        delete s;
        delete t;
    }

    Actor::Actor(const Actor &other) :
        rect(other.rect), velocity(other.velocity)
    {
        if (s != nullptr) {
            delete s;
        }
        s = new lua::Script(other.s->name);
        lua::actor::add(s->s);
        lua::actorman::add(s->s);
        s->call();

        lua_getglobal(s->s, TABLENAME);
        auto me_table = lua_gettop(s->s);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, TABLENAME " table not found");
        }
        auto tileset = s->get_field("tileset");
        lua_pushlightuserdata(s->s, this);
        lua_setfield(s->s, me_table, "self");
        lua_pushnumber(s->s, this->handle);
        lua_setfield(s->s, me_table, "handle");
        lua_pushlightuserdata(s->s, manager);
        lua_setfield(s->s, me_table, "manager");
        this->t = new render::TileSet(other.t->get_name());
        set_tileset(0);
        this->current_tile = tileset_cache[0];
    }

    void Actor::init()
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, "actor table not found");
        }
        auto actor_table = lua_gettop(s->s);
        lua_getfield(s->s, actor_table, "init");
        lua_pcall(s->s, 0, 0, 0);
    }

    void Actor::update(int delta)
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, "actor table not found");
        }
        auto actor_table = lua_gettop(s->s);
        lua_getfield(s->s, actor_table, "update");
        if (!lua_isfunction(s->s, -1)) {
            lua::error(s->s, "event function not found");
        }
        lua_pushnumber(s->s, delta);
        if (lua_pcall(s->s, 1, 0, 0) != 0) {
            lua::error(s->s, "update function failed");
        }
        lua_settop(s->s, actor_table - 1);

        current_tile->update(delta);
    }

    void Actor::commit_update(int delta)
    {
        this->current_tile->set_location(sf::Vector2i(this->rect.left, this->rect.top));
        this->current_tile->set_scale(this->scale);
        this->current_tile->set_origin(this->origin);
    }

    void Actor::draw(sf::RenderWindow &window)
    {
        current_tile->draw(window);
#if DEBUG
        auto x = sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
        x.setPosition(sf::Vector2f(rect.left, rect.top));
        x.setFillColor(sf::Color::Transparent);
        x.setOutlineColor(sf::Color::Blue);
        x.setOutlineThickness(5);
        window.draw(x);
#endif //DEBUG
    }

    void Actor::hurt(pain p)
    {

    }

    sf::FloatRect Actor::get_rect() const
    {
        return this->rect;
    }

    std::string Actor::get_name() const
    {
        return this->name;
    }

    void Actor::set_rect(sf::FloatRect& x)
    {
        this->rect = x;
    }

    void Actor::set_location(sf::Vector2f x)
    {
        this->rect.left = x.x;
        this->rect.top = x.y;
    }

    sf::Vector2f Actor::get_velocity() const
    {
        return this->velocity;
    }

    void Actor::set_velocity(sf::Vector2f vel)
    {
        this->velocity = vel;
    }

    void Actor::set_scale(sf::Vector2f scale)
    {
        this->scale = scale;
    }

    void Actor::set_origin(sf::Vector2f origin)
    {
        this->origin = origin;
    }

    void Actor::set_tileset(int i)
    {
        if (tileset_cache.size() > i && tileset_cache[i] != nullptr) {
            current_tile = tileset_cache[i];
            return;
        }
        while (tileset_cache.size() < i+1) {
            tileset_cache.push_back(tile_ptr());
        }
        tileset_cache[i].reset(t->spawn(i, sf::Vector2i(rect.left, rect.top)));
        current_tile = tileset_cache[i];
    }

    tile_ptr Actor::get_tile()
    {
        return this->current_tile;
    }

    Actor *Actor::clone() 
    {
        return new Actor(*this);
    }
};


