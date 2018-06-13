#include "Scene.h"

#define TABLENAME "me"

namespace scene {
    Scene::Scene(std::string name, sf::Vector2i size) : size(size), name(name)
    {
        std::string filename = SCENEDIR;
        filename += name;
        filename += ".lua";
        s = new lua::Script(filename);
        s->call();

        lua_getglobal(s->s, TABLENAME);
        auto me_table = lua_gettop(s->s);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, TABLENAME " table not found");
        }
        lua_pushlightuserdata(s->s, this);
        lua_setfield(s->s, me_table, "self");
    }

    Scene::~Scene()
    {
        delete s;
    }

    void Scene::update(int delta, sf::RenderWindow &window)
    {
        menu.update(delta, window);

        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "update");
        if (!lua_isfunction(s->s, -1)) {
            return;
        }
        lua_pushnumber(s->s, delta);
        if (lua_pcall(s->s, 1, 0, 0) != 0) {
            lua::error(s->s, "update function failed");
        }
        lua_settop(s->s, me_table - 1);
    }

    void Scene::draw(sf::RenderWindow &window)
    {
        menu.draw(window);
    }

    void Scene::wakeup(sf::String message)
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "wakeup");
        if (!lua_isfunction(s->s, -1)) {
            return;
        }
        lua_pushstring(s->s, message.toAnsiString().c_str());
        if (lua_pcall(s->s, 1, 0, 0)) {
            lua::error(s->s, "wakeup function failed");
        }
        lua_settop(s->s, me_table - 1);
    }

    sf::String Scene::sleep()
    {
        return sf::String(); 
    }

    sf::String Scene::pop()
    {
        return sf::String();
    }

    Scene::Status Scene::status()
    {
        return this->state;
    }

    Scene *Scene::new_scene()
    {
        return this->next_scene;
    }

    void Scene::reset_status()
    {
        this->state = nothing;
        this->next_scene = nullptr;
    }
};

