#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>

#include "Scene.h"

#include "MusicManager.h"
#include "Hero.h"
#include "Tile.h"

class GameScene : public Scene
{
public:
    GameScene(sf::Vector2i size);
    ~GameScene();

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    sf::View main_window;

    Hero hero;
    std::vector<Tile> tileset;

    Scene::Status state;
    Scene* next_scene;

    bool first_loop = true;
};

#endif // GAMESCENE_H
