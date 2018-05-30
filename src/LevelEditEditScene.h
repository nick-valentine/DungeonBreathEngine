#ifndef LEVELEDITEDITSCENE_H
#define LEVELEDITEDITSCENE_H

#include <fstream>
#include <sstream>

#include "World.h"
#include "Scene.h"
#include "ButtonGroup.h"
#include "Exceptions.h"

class LevelEditEditScene : public Scene
{
public:
    LevelEditEditScene(sf::Vector2i size, std::string name);
    ~LevelEditEditScene() = default;

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    void load_level();
    void save_level();

    sf::View main_window;

    Scene::Status state = Scene::Status::nothing;
    Scene *next_scene = nullptr;

    std::unique_ptr<World> world = nullptr;

    std::string title;
    std::string name;
    std::string tileset;

    ButtonGroup menu;


};

#endif //LEVELEDITEDITSCENE_H
