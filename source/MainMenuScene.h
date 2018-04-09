#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Scene.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene(sf::Vector2i size);
    ~MainMenuScene();

    void update(int delta, sf::RenderWindow &window, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    Scene::Status state;
};

#endif // MAINMENUSCENE_H
