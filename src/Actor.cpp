#include "Actor.h"

#define TABLENAME "me"

Actor::Actor(sf::Vector2i pos, sf::Vector2i scale, Input *input, Logger *logger) :
	s("hero.lua", input, logger), t(nullptr), current_tile(nullptr),
	input(input), logger(logger), tileset_cache()
{
	this->rect = sf::Rect<int>(pos.x, pos.y, scale.x, scale.y);
	this->velocity = sf::Vector2f(0, 0);

	s.call();

	lua_getglobal(s.s, TABLENAME);
	if (!lua_istable(s.s, -1)) {
		lua::error(s.s, "actor table not found1");
	}
	auto tileset = s.get_field("tileset");
	t = new TileSet(tileset);
	tileset_cache.push_back(t->spawn(0, pos));
	current_tile = tileset_cache[0];
}

Actor::~Actor()
{
	delete t;
	delete current_tile;
}

Actor::Actor(const Actor &other) :
	s(other.s.name, other.input, other.logger), rect(other.rect),
	velocity(other.velocity), input(other.input), logger(other.logger),
	tileset_cache()
{
	this->t = new TileSet(other.t->get_name());
	this->current_tile = this->t->spawn(0, sf::Vector2i(this->rect.left, this->rect.top));
}

void Actor::update(int delta, Input *input, Logger *logger)
{
	lua_getglobal(s.s, TABLENAME);
	if (!lua_istable(s.s, -1)) {
		lua::error(s.s, "actor table not found2");
	}
	auto actor_table = lua_gettop(s.s);
	lua_getfield(s.s, actor_table, "update");
	lua_pushnumber(s.s, delta);
	if (lua_pcall(s.s, 1, 0, 0) != 0) {
		lua::error(s.s, "update function failed");
	}
	lua_settop(s.s, actor_table - 1);

	current_tile->update(delta);

    this->rect.left += int(this->velocity.x);
    this->rect.top += int(this->velocity.y);
}

void Actor::draw(sf::RenderWindow &window)
{
	current_tile->draw(window);
}

void Actor::hurt(pain p)
{

}

sf::Rect<int> Actor::get_rect() const
{
        return this->rect;
}

void Actor::set_rect(sf::Rect<int>& x)
{
    this->rect = x;
}

sf::Vector2f Actor::get_velocity() const
{
    return this->velocity;
}

void Actor::set_velocity(sf::Vector2f vel)
{
    this->velocity = vel;
}

void Actor::set_tileset(int i)
{
	if (tileset_cache.size() > i && tileset_cache[i] != nullptr) {
		current_tile = tileset_cache[i];
		return;
	}
	while (tileset_cache.size() > i) {
		tileset_cache.push_back(nullptr);
	}
	tileset_cache[i] = t->spawn(i, sf::Vector2i(rect.left, rect.top));
}

Actor *Actor::clone() 
{
	return new Actor(*this);
}

void lua::actor::add(lua_State *L)
{
	static const struct luaL_Reg mylib[] = {
		{ "get_rect", get_rect },
		{ "get_velocity", get_velocity },
		{ "set_velocity", set_velocity },
		{ "set_tileset", set_tileset },
		{ NULL, NULL }
	};
	lua_getglobal(L, "actor");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, mylib, 0);

	//lua_pushlightuserdata(S, l);
	//lua_setfield(S, -2, "log");

	lua_setglobal(L, "actor");
}

int lua::actor::get_rect(lua_State *L)
{
	return 0;
}

int lua::actor::get_velocity(lua_State *L)
{
	return 0;
}

int lua::actor::set_velocity(lua_State *L)
{
	return 0;
}

int lua::actor::set_tileset(lua_State *L)
{
	return 0;
}
