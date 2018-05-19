#include "TileSetNewScene.h"
#include "TileSetScene.h"
#include "TileSetEditScene.h"

TileSetNewScene::TileSetNewScene(sf::Vector2i size) : Scene(size), keyboard(size)
{
    menu.add_button("name", &name);
    menu.add_button("spritesheet", &spritesheet);
    menu.add_button("basesize", &base_size);
    menu.add_button("proceed", &proceed);
    menu.add_button("back", &back);
}

TileSetNewScene::~TileSetNewScene()
{

}

void TileSetNewScene::update(int delta, sf::RenderWindow &window)
{
    if (pl_state == in_menu) {
        return update_menu(delta, window);
    }
    update_keyboard(delta, window);
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

void TileSetNewScene::update_menu(int delta, sf::RenderWindow &window)
{
    menu.update(delta, app_container.get_input(), window);
    auto pressed = this->menu.neg_edge_button();

    if (pressed == "proceed") {
        write_tileset_meta();
        this->next_scene = new TileSetEditScene(this->size, name.get_label());
        this->state = Scene::Status::switch_scene;
    } else if (pressed == "name") {
        pl_state = in_keyboard;
        current_button = &name;
        keyboard.set_input("");
    } else if (pressed == "spritesheet") {
        pl_state = in_keyboard;
        current_button = &spritesheet;
        keyboard.set_input("");
    } else if (pressed == "basesize") {
        pl_state = in_keyboard;
        current_button = &base_size;
        keyboard.set_input("");
    }else if (pressed == "back") {
        this->next_scene = new TileSetScene(size);
        this->state = Scene::Status::switch_scene;
    }
}

void TileSetNewScene::draw_menu(sf::RenderWindow &window)
{
    name_label.draw(window);
    spritesheet_label.draw(window);
    base_size_label.draw(window);
    menu.draw(window);
}

void TileSetNewScene::update_keyboard(int delta, sf::RenderWindow &window)
{
    keyboard.update(delta, window);
    if (app_container.get_input()->is_key_pressed(Input::escape) || keyboard.status() == Scene::Status::switch_scene) {
        keyboard.reset_status();
		app_container.get_logger()->info(keyboard.get_input().toAnsiString().c_str());
        current_button->set_label(keyboard.get_input());
        pl_state = in_menu;
    }
}

void TileSetNewScene::draw_keyboard(sf::RenderWindow &window)
{
    keyboard.draw(window);
}

void TileSetNewScene::write_tileset_meta()
{
    std::fstream index(TILESETDIR "index.txt", std::fstream::out | std::fstream::app);
    index<<name.get_label().toUtf8().c_str()<<"\n";
    index.close();

    // @todo: this breaks internationalizatin a bit
    std::string filename = name.get_label().toAnsiString(); 
    filename += ".txt";
    std::ofstream datafile(TILESETDIR + filename);
    datafile<<name.get_label().toUtf8().c_str()<<"\n";
    datafile<<"size "<<base_size.get_label().toUtf8().c_str()<<"\n";
    datafile<<"tex "<<spritesheet.get_label().toUtf8().c_str()<<"\n";
    datafile.close();
}
