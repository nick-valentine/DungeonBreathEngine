#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>

#include "Scene.h"

#include "core.h"
#include "audio.h"
#include "play.h"

namespace scene {
    class Game : public Scene
    {
    public:
        Game(sf::Vector2i size);
        ~Game();

        void update(int delta, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        Scene::Status status();
        Scene *new_scene();
        void reset_status();
    private:
        sf::View main_window;

        play::WorldManager world;

        Scene::Status state = Scene::Status::nothing;
        Scene* next_scene = nullptr;

        bool first_loop = true;
    };
};

#endif // GAMESCENE_H
