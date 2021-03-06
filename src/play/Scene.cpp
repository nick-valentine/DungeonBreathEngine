#include "Scene.h"

#define TABLENAME "me"

namespace play {
    Scene::Scene(std::string name, sf::Vector2i size) : size(size), name(name)
    {
        this->reset_camera();
        menu = new ui::Menu();

        std::string filename = SCENEDIR;
        filename += name;
        filename += ".lua";
        s = new lua::Script(filename);
        lua::l_scene::add(s->s);
        lua::l_ui::add(s->s);
        s->call();

        lua_getglobal(s->s, TABLENAME);
        auto me_table = lua_gettop(s->s);
        if (!lua_istable(s->s, -1)) {
            lua::call_error(s->s, TABLENAME " table not found");
        }
        lua_pushlightuserdata(s->s, this);
        lua_setfield(s->s, me_table, "self");

        init();
    }

    Scene::~Scene()
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::call_error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "release");
        if (lua_isfunction(s->s, -1)) {
            if (lua_pcall(s->s, 0, 0, 0) != 0) {
                lua::call_error(s->s, "release function failed");
            }
            lua_settop(s->s, me_table - 1);
        }

        if (world != nullptr) {
            delete world;
        }
        delete s;
        delete menu;
    }

    void Scene::update(int delta, sf::RenderWindow &window)
    {
        menu->update(delta, window);

        if (world != nullptr) {
            world->update(delta, window);
        }

        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::call_error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "update");
        if (!lua_isfunction(s->s, -1)) {
            return;
        }
        lua_pushnumber(s->s, delta);
        if (lua_pcall(s->s, 1, 0, 0) != 0) {
            lua::call_error(s->s, "update function failed");
        }
        lua_settop(s->s, me_table - 1);
    }

    void Scene::draw(sf::RenderTarget &window)
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::call_error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "draw");
        if (!lua_isfunction(s->s, -1)) {
            return render(window);
        }
        lua_pushlightuserdata(s->s, &window);
        if (lua_pcall(s->s, 1, 0, 0) != 0) {
            lua::call_error(s->s, "draw function failed");
        }
        lua_settop(s->s, me_table - 1);
    }

    void Scene::render(sf::RenderTarget &window)
    {
        window.setView(this->main_window);
        menu->draw(window);
        if (world != nullptr) {
            world->draw(window);
        }
    }

    void Scene::init()
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::call_error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "init");
        if (!lua_isfunction(s->s, -1)) {
            return;
        }
        if (lua_pcall(s->s, 0, 0, 0)) {
            lua::call_error(s->s, "init function failed");
        }
        lua_settop(s->s, me_table - 1);
    }

    void Scene::wakeup(sf::String message)
    {
        lua_getglobal(s->s, TABLENAME);
        if (!lua_istable(s->s, -1)) {
            lua::call_error(s->s, TABLENAME " table not found");
        }
        auto me_table = lua_gettop(s->s);
        lua_getfield(s->s, me_table, "wakeup");
        if (!lua_isfunction(s->s, -1)) {
            return;
        }
        lua_pushstring(s->s, message.toAnsiString().c_str());
        if (lua_pcall(s->s, 1, 0, 0)) {
            lua::call_error(s->s, "wakeup function failed");
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

    void Scene::indicate_push(std::string name)
    {
        this->state = push_scene;
        this->next_scene = new Scene(name, size);
    }

    void Scene::indicate_pop()
    {
        this->state = pop_scene;
        this->next_scene = nullptr;
    }

    ui::Menu *Scene::get_menu()
    {
        return this->menu;
    }

    sf::Vector2i Scene::get_size() const
    {
        return this->size;
    }

    void Scene::reset_camera()
    {
        this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    }

    sf::Vector2f Scene::get_camera_center()
    {
        return this->main_window.getCenter();
    }

    void Scene::move_camera(sf::Vector2f diff)
    {
        this->main_window.move(diff);
    }

    void Scene::set_viewport(sf::FloatRect c)
    {
        this->main_window.setViewport(c);
    }

    sf::FloatRect Scene::get_viewport()
    {
        return this->main_window.getViewport();
    }

    void Scene::zoom_camera(float factor)
    {
        this->main_window.zoom(factor);
    }

    void Scene::apply_view(sf::RenderTarget &window)
    {
        window.setView(this->main_window);
    }

    void Scene::init_world()
    {
        this->world = new play::WorldManager();
    }

    play::World *Scene::get_world()
    {
        return world->get().get();
    }
};

