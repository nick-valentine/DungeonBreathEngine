#include "TileSetEditScene.h"
#include "TileSetScene.h"

#include <iostream>

TileSetEditScene::TileSetEditScene(sf::Vector2i size, std::string tileset) : Scene(size),
    state(Scene::nothing),
    next_scene(nullptr),
    tileset(tileset),
    tileset_label(sf::IntRect(100, 100, 300, 50), Strings::utf8_to_sfml(tileset)),
    back(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("optionsmenu.back_button"))
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    menu.add_button("exit_menu", &back);
}

TileSetEditScene::~TileSetEditScene()
{

}

void TileSetEditScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    menu.update(delta, input, window);
    std::string pressed = this->menu.pressed_button();

    if (pressed == "exit_menu") {
        this->next_scene = new TileSetScene(this->size);
        this->state = Scene::switch_scene;
    }
}

void TileSetEditScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    menu.draw(window);
    tileset_label.draw(window);
}

Scene::Status TileSetEditScene::status()
{
    return state;
}

Scene *TileSetEditScene::new_scene()
{
    return next_scene;
}
