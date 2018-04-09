#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Scene.h"
#include "Button.h"

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
    sf::View main_window;

    Scene::Status state;
    Scene* next_scene;

    Button play_button;
    Button exit_button;
};

#endif // MAINMENUSCENE_H
