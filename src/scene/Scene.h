#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Macros.h"
#include "core.h"
#include "ui.h"
#include "script.h"

namespace scene {
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
        virtual ~Scene();

        virtual void update(int delta, sf::RenderWindow &window);
        virtual void draw(sf::RenderWindow &window);

        virtual void init();
        virtual void wakeup(sf::String message);
        virtual sf::String sleep();
        virtual sf::String pop();
        virtual Status status();
        virtual Scene *new_scene();
        virtual void reset_status();

        virtual void indicate_push(std::string name);
        virtual void indicate_pop();

        virtual ui::Menu *get_menu();
        virtual sf::Vector2i get_size() const;
    protected:
        Status state = nothing;
        Scene* next_scene = nullptr;

        sf::Vector2i size;

        std::string name;
        lua::Script *s;

        ui::Menu *menu;
    };
};

#endif // SCENE_H
