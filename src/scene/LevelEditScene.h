#ifndef LEVELEDITSCENE_H
#define LEVELEDITSCENE_H

#include "core.h"
#include "Scene.h"
#include "ui.h"

class LevelEditScene : public Scene
{
public:
    LevelEditScene(sf::Vector2i size);
    ~LevelEditScene() = default;

    void update(int delta, sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    Scene::Status status();
    Scene *new_scene();
    void reset_status();
private:
    sf::View main_window;

    core::Index index = core::Index(LEVELDIR);

    Scene::Status state = Scene::nothing;
    Scene *next_scene = nullptr;

    ButtonGroup menu;
    std::vector<TextButton> levels;
    TextButton new_level = TextButton(sf::IntRect(size.x - 400, size.y - 160, 300, 50), core::StringProvider::get("leveleditmenu.new"));
    TextButton back = TextButton(sf::IntRect(size.x - 400, size.y - 100, 300, 50), core::StringProvider::get("leveleditmenu.back"));
};

#endif //LEVELEDITSCENE_H
