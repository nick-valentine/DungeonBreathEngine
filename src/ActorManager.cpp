#include "ActorManager.h"
#include "Actor.h"

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
    actor_ptr tmp(new Actor(this, max_id, pos, sf::Vector2f(1, 1), filename));
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

void lua::actorman::add(lua_State *L)
{
    static const struct luaL_Reg mylib[] = {
        { "spawn", spawn },
        { "remove", remove },
        { "clear", clear },
        { "set_camera_target", set_camera_target },
        { "get_camera_target", get_camera_target },
        { NULL, NULL }
    };
    lua_getglobal(L, "actor_manager");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
    }
    luaL_setfuncs(L, mylib, 0);

    lua_setglobal(L, "actor_manager");
}

int lua::actorman::spawn(lua_State *L)
{
    auto a = (ActorManager *)lua_touserdata(L, -3);
    std::string name = lua_tostring(L, -2);
    auto x = lua::get_num_field(L, "x");
    auto y = lua::get_num_field(L, "y");
    auto h = a->spawn(name, sf::Vector2i(x, y));
    lua_pushnumber(L, h);
    return 1;
}

int lua::actorman::remove(lua_State *L)
{
    auto a = (ActorManager *)lua_touserdata(L, -2);
    if (!lua_isnumber(L, -1)) {
        lua::error(L, "param 1 not number");
    }
    auto h = (int) lua_tonumber(L, -1);
    a->remove(h);
    return 0;
}

int lua::actorman::clear(lua_State *L)
{
    auto a = (ActorManager *)lua_touserdata(L, -1);
    a->clear();
    return 0;
}

int lua::actorman::set_camera_target(lua_State *L)
{
    auto a = (ActorManager *)lua_touserdata(L, -2);
    if (!lua_isnumber(L, -1)) {
        lua::error(L, "param 1 not number");
    }
    auto h = (int) lua_tonumber(L, -1);
    a->set_camera_target(h);
    return 0;
}

int lua::actorman::get_camera_target(lua_State *L)
{
    auto a = (ActorManager *)lua_touserdata(L, -2);
    auto t = a->get_camera_target();
    lua_pushlightuserdata(L, t.get());
    return 1;
}
