#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>

#include "Scene.h"

#include "core.h"
#include "MusicManager.h"
#include "play.h"

class GameScene : public Scene
{
public:
    GameScene(sf::Vector2i size);
    ~GameScene();

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    sf::View main_window;

    WorldManager world;

    Scene::Status state = Scene::Status::nothing;
    Scene* next_scene = nullptr;

    bool first_loop = true;
};

#endif // GAMESCENE_H
