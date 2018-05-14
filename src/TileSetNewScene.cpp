#include "TileSetNewScene.h"
#include "TileSetScene.h"

TileSetNewScene::TileSetNewScene(sf::Vector2i size) : Scene(size),
    state(Scene::nothing),
    next_scene(nullptr),
    name(sf::IntRect(10, 100, 300, 50)),
    proceed(sf::IntRect(size.x - 400, size.y - 160, 300, 50), StringProvider::get("tilesetnewmenu.proceed")),
    back(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("tilesetnewmenu.back"))
{
    menu.add_button("name", &name);
    menu.add_button("proceed", &proceed);
    menu.add_button("back", &back);
}

TileSetNewScene::~TileSetNewScene()
{

}

void TileSetNewScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    menu.update(delta, input, window);
    auto pressed = this->menu.neg_edge_button();

    if (pressed == "proceed") {
        logger->info("todo: proceed");
    } else if (pressed == "back") {
        this->next_scene = new TileSetScene(size);
        this->state = Scene::Status::switch_scene;
    }
}

void TileSetNewScene::draw(sf::RenderWindow &window)
{
    menu.draw(window);
}

Scene::Status TileSetNewScene::status()
{
    return state;
}

Scene *TileSetNewScene::new_scene()
{
    return next_scene;
}
