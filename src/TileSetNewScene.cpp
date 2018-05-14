#include "TileSetNewScene.h"
#include "TileSetScene.h"

TileSetNewScene::TileSetNewScene(sf::Vector2i size) : Scene(size),
    state(Scene::nothing),
    next_scene(nullptr),
    name(sf::IntRect(100, 100, 300, 50), ""),
    proceed(sf::IntRect(size.x - 400, size.y - 160, 300, 50), StringProvider::get("tilesetnewmenu.proceed")),
    back(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("tilesetnewmenu.back")),
    pl_state(in_menu),
                                                      keyboard(size)
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
    if (pl_state == in_menu) {
        return update_menu(delta, window, input, logger);
    }
    update_keyboard(delta, window, input, logger);
}

void TileSetNewScene::draw(sf::RenderWindow &window)
{
    if (pl_state == in_menu) {
        return draw_menu(window);
    }
    draw_keyboard(window);
}

Scene::Status TileSetNewScene::status()
{
    return state;
}

Scene *TileSetNewScene::new_scene()
{
    return next_scene;
}

void TileSetNewScene::update_menu(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    menu.update(delta, input, window);
    auto pressed = this->menu.neg_edge_button();

    if (pressed == "proceed") {
        logger->info("todo: proceed");
    } else if (pressed == "name") {
        pl_state = in_keyboard;
        keyboard.set_input("");
    } else if (pressed == "back") {
        this->next_scene = new TileSetScene(size);
        this->state = Scene::Status::switch_scene;
    }
}

void TileSetNewScene::draw_menu(sf::RenderWindow &window)
{
    menu.draw(window);
}

void TileSetNewScene::update_keyboard(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    keyboard.update(delta, window, input, logger);
    if (input->is_key_pressed(Input::escape)) {
        logger->info(keyboard.get_input().toAnsiString().c_str());
        pl_state = in_menu;
    }
}

void TileSetNewScene::draw_keyboard(sf::RenderWindow &window)
{
    keyboard.draw(window);
}
