#ifndef LEVELEDITACTORSELECT_H
#define LEVELEDITACTORSELECT_H

#include "core.h"
#include "Scene.h"
#include "ui.h"

class LevelEditActorSelectScene : public Scene
{
public:
    LevelEditActorSelectScene(sf::Vector2i size);
    ~LevelEditActorSelectScene() = default;

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    std::string get_selected();

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    sf::View main_window;

    Index index = Index(SCRIPTDIR ACTORDIR);

    Scene::Status state = Scene::nothing;
    Scene *next_scene = nullptr;
    std::string selected = "";

    ButtonGroup menu;
    std::vector<TextButton> actors;
};

#endif //LEVELEDITACTORSELECT_H
