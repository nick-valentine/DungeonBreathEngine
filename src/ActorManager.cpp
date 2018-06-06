#include "ActorManager.h"
#include "Actor.h"

ActorManager::ActorManager()
{
    // @todo: make this use index instead
    std::fstream ifile(SCRIPTDIR ACTORDIR "index.txt");
    std::string temp;
    ifile >> temp;
    while (ifile.good()) {
        available_actors.push_back(temp);
        ifile >> temp;
    }
    ifile.close();

    //@todo: this is code for testing
    collision_boxes.push_back(sf::FloatRect(0,0,100,100));
    collision_boxes.push_back(sf::FloatRect(100,0,100,100));
}

void ActorManager::update(int delta)
{
    for (auto &i : actors) {
        i.second->update(delta);
        this->check_collision(i.second);
        i.second->commit_update(delta);
    }
}

void ActorManager::draw(sf::RenderWindow &window)
{
    for (auto &i : actors) {
        i.second->draw(window);
    }

    for (auto &i : collision_boxes) {
        auto x = sf::RectangleShape(sf::Vector2f(i.width, i.height));
        x.setPosition(sf::Vector2f(i.left, i.top));
        x.setFillColor(sf::Color::White);

        window.draw(x);

    }
}

int ActorManager::spawn(std::string name, sf::Vector2i pos)
{
    if (!check_available(name)) {
        throw new UnavailableActorException();
    }
    actor_ptr tmp(new Actor(this, max_id, pos, sf::Vector2f(64, 64), name));
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


std::string ActorManager::get_actor_data() const
{
    std::stringstream ss;
    for (const auto &i : actors) {
        auto rect = i.second->get_rect();
        ss<<i.second->get_name()<<" "<<rect.left<<" "<<rect.top<<"\n";
    }
    return ss.str();
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

void ActorManager::check_collision(actor_ptr a)
{
    auto rect = a->get_rect();
    auto vel = a->get_velocity();
    rect.top += vel.y;
    rect.left += vel.x;
    auto intersection = sf::FloatRect();
    for (const auto &i : collision_boxes) {
        if (i.intersects(rect, intersection)) {
            resolve_collision(rect, i, intersection);
        }
    }
    a->set_rect(rect);
}

void ActorManager::resolve_collision(sf::FloatRect &a_rect, const sf::FloatRect &with, const sf::FloatRect &intersect)
{
    if (intersect.height < intersect.width) {
        // resolve y intersection
        if (a_rect.top < with.top) {
            // actor on top, move up
            a_rect.top -= intersect.height;
        } else {
            // otherwise move down
            a_rect.top += intersect.height;
        }
    } else {
        // resolve x intersection
        if (a_rect.left < with.left) {
            // actor on left, move left
            a_rect.left -= intersect.width;
        } else {
            // otherwise move right
            a_rect.left += intersect.width;
        }
    }
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
