#include "Actor.h"

#define TABLENAME "me"

Actor::Actor(ActorManager *man, int handle, sf::Vector2i pos, sf::Vector2f scale, std::string name) : manager(man), name(name)
{
    std::string filename = ACTORDIR;
    filename += name;
    filename += ".lua";
    s = new Script(filename);
    this->handle = handle;
    this->rect = sf::FloatRect(pos.x, pos.y, scale.x, scale.y);
    this->velocity = sf::Vector2f(0, 0);
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
    lua_pushlightuserdata(s->s, man);
    lua_setfield(s->s, me_table, "manager");

    t = new TileSet(tileset);
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
    s = new Script(other.s->name);
    this->t = new TileSet(other.t->get_name());
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

void lua::actor::add(lua_State *L)
{
    static const struct luaL_Reg mylib[] = {
        { "get_rect", get_rect },
        { "set_scale", set_scale },
        { "set_origin", set_origin },
        { "set_collision_bounds", set_collision_bounds },
        { "get_velocity", get_velocity },
        { "set_velocity", set_velocity },
        { "set_tileset", set_tileset },
        { "pause_anim", pause_anim },
        { "play_anim", play_anim },
        { "reset_anim", reset_anim },
        { NULL, NULL }
    };
    lua_getglobal(L, "actor");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
    }
    luaL_setfuncs(L, mylib, 0);

    lua_setglobal(L, "actor");
}

int lua::actor::get_rect(lua_State *L)
{
    Actor *a = (Actor *)lua_touserdata(L, -1);
    sf::FloatRect rect;
    if (a != nullptr) {
        app_container.get_logger()->debug("get_rect called with null actor");
        rect = a->get_rect();
    }
    lua_newtable(L);
    auto table = lua_gettop(L);
    lua_pushnumber(L, rect.left);
    lua_setfield(L, table, "left");
    lua_pushnumber(L, rect.top);
    lua_setfield(L, table, "top");
    lua_pushnumber(L, rect.width);
    lua_setfield(L, table, "width");
    lua_pushnumber(L, rect.height);
    lua_setfield(L, table, "height");
    return 1;
}

int lua::actor::set_scale(lua_State *L)
{
    Actor *a = (Actor *)lua_touserdata(L, -2);
    if (a == nullptr) {
        return 0;
    }
    auto x = lua::get_num_field(L, "x");
    auto y = lua::get_num_field(L, "y");
    a->set_scale(sf::Vector2f(x, y));
    return 0;
}

int lua::actor::set_origin(lua_State *L)
{
    Actor *a = (Actor *)lua_touserdata(L, -2);
    if (a == nullptr) {
        return 0;
    }
    auto x = lua::get_num_field(L, "x");
    auto y = lua::get_num_field(L, "y");
    a->set_origin(sf::Vector2f(x, y));
    return 0;
}

int lua::actor::set_collision_bounds(lua_State *L)
{
    Actor *a = (Actor *)lua_touserdata(L, -2);
    if (a == nullptr) {
        return 0;
    }
    auto x = lua::get_num_field(L, "x");
    auto y = lua::get_num_field(L, "y");
    auto rect = a->get_rect();
    rect.width = x;
    rect.height = y;
    a->set_rect(rect);
    return 0;
}

int lua::actor::get_velocity(lua_State *L)
{
    Actor *a = (Actor *)lua_touserdata(L, -1);
    sf::Vector2f vel;
    if (a != nullptr) {
        vel = a->get_velocity();
    }
    lua_newtable(L);
    auto table = lua_gettop(L);
    lua_pushnumber(L, vel.x);
    lua_setfield(L, table, "x");
    lua_pushnumber(L, vel.y);
    lua_setfield(L, table, "y");
    return 1;
}

int lua::actor::set_velocity(lua_State *L)
{
    auto a = (Actor *)lua_touserdata(L, -2);
    if (a == nullptr) {
        return 0;
    }
    auto x = lua::get_num_field(L, "x");
    auto y = lua::get_num_field(L, "y");
    a->set_velocity(sf::Vector2f(x, y));
    return 0;
}

int lua::actor::set_tileset(lua_State *L)
{
    auto a = (Actor *)lua_touserdata(L, -2);
    if (a == nullptr) {
        return 0;
    }
    if (!lua_isnumber(L, -1)) {
        lua::error(L, "param 1 not number");
    }
    auto i = (int) lua_tonumber(L, -1);
    a->set_tileset(i);
    return 0;
}

int lua::actor::pause_anim(lua_State *L)
{
    auto a = (Actor *)lua_touserdata(L, -1);
    if (a == nullptr) {
        return 0;
    }
    a->get_tile()->pause();
    return 0;
}

int lua::actor::play_anim(lua_State *L)
{
    auto a = (Actor *)lua_touserdata(L, -1);
    if (a == nullptr) {
        return 0;
    }
    a->get_tile()->play();
    return 0;
}

int lua::actor::reset_anim(lua_State *L)
{
    auto a = (Actor *)lua_touserdata(L, -1);
    if (a == nullptr) {
        return 0;
    }
    a->get_tile()->reset();
    return 0;
}
