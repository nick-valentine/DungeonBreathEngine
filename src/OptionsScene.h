#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "StringProvider.h"
#include "MusicManager.h"
#include "Scene.h"
#include "ButtonGroup.h"
#include "Button.h"

class OptionsScene : public Scene
{
public:
    OptionsScene(sf::Vector2i size);
    ~OptionsScene() = default;

    void update(int delta, sf::RenderWindow &window, Input *input, Logger *logger);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
private:
    sf::View main_window;

    Scene::Status state;
    Scene *next_scene;

    Button back_button;
    ButtonGroup menu;
};

#endif //OPTIONSSCENE_H
