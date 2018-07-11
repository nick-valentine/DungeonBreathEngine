#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Macros.h"
#include "core.h"
#include "World.h"
#include "WorldManager.h"
#include "ActorManager.h"
#include "Actor.h"
#include "ui.h"
#include "script.h"

namespace play {
    class Scene
    {
    public:
        enum Status {
            nothing,
            exit_program,
            push_scene,
            pop_scene,
        };

        Scene(std::string name, sf::Vector2i size);
        ~Scene();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderTarget &window);
        void render(sf::RenderTarget &window);

        void init();
        void wakeup(sf::String message);
        sf::String sleep();
        sf::String pop();
        Status status();
        Scene *new_scene();
        void reset_status();

        void indicate_push(std::string name);
        void indicate_pop();

        ui::Menu *get_menu();
        sf::Vector2i get_size() const;

        void reset_camera();
        sf::Vector2f get_camera_center();
        void move_camera(sf::Vector2f diff);
        void set_viewport(sf::FloatRect c);
        sf::FloatRect get_viewport();
        void zoom_camera(float factor);
        void apply_view(sf::RenderTarget &window);

        void init_world();
        play::World *get_world();
    protected:
        Status state = nothing;
        Scene* next_scene = nullptr;

        sf::View main_window;

        sf::Vector2i size;

        std::string name;
        lua::Script *s;

        ui::Menu *menu;
        play::WorldManager *world = nullptr;
    };
};

#endif // SCENE_H
