#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"

#include "MusicManager.h"
#include "Hero.h"
#include "Tile.h"

class GameScene : public Scene
{
public:
    GameScene(sf::Vector2i size);
    ~GameScene();

    void update(int delta, sf::RenderWindow &window, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    sf::View main_window;

    Hero hero;
    Tile tile;

    Scene::Status state;
    Scene* next_scene;

    bool first_loop = true;
};

#endif // GAMESCENE_H
