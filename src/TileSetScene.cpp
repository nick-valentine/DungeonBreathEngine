#include "TileSetScene.h"
#include "TileSetEditScene.h"
#include "MainMenuScene.h"

TileSetScene::TileSetScene(sf::Vector2i size) : Scene(size),
    state(Scene::nothing),
    next_scene(nullptr),
    back(sf::IntRect(size.x - 400, size.y - 100, 300, 50), StringProvider::get("optionsmenu.back_button"))
{
    std::vector<std::string> tileset_index;
    std::ifstream ifile(TILESETDIR "index.txt");

    if (!ifile.good()) {
        throw FileNotFoundException();
    }

    std::string temp;
    ifile>>temp;
    while (ifile.good()) {
        tileset_index.push_back(temp);
        ifile>>temp;
    } 

    ifile.close();

    for (size_t i = 0; i < tileset_index.size(); ++i) {
        TextButton temp(sf::IntRect(10, (i+1) * 50, 300, 50), Strings::utf8_to_sfml(tileset_index[i]));

        tilesets.push_back(temp);
        menu.add_button(tileset_index[i], &tilesets[i]);
    }
    menu.add_button("exit_menu", &back);
}

TileSetScene::~TileSetScene()
{

}

void TileSetScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    menu.update(delta, input, window);
    std::string pressed = this->menu.neg_edge_button();

    if (pressed == "exit_menu") {
        this->next_scene = new MainMenuScene(this->size);
        this->state = Scene::Status::switch_scene;
    } else if (pressed != "") {
        this->next_scene = new TileSetEditScene(this->size, pressed);
        this->state = Scene::Status::switch_scene;
    }
}

void TileSetScene::draw(sf::RenderWindow &window)
{
    menu.draw(window);
}

Scene::Status TileSetScene::status()
{
    return state;
}

Scene *TileSetScene::new_scene()
{
    return next_scene;
}
