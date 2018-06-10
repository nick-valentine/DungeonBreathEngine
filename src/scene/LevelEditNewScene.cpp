#include "LevelEditNewScene.h"
#include "LevelEditEditScene.h"

LevelEditNewScene::LevelEditNewScene(sf::Vector2i size) : Scene(size), keyboard(size)
{
    menu.add_button("name", &name);
    menu.add_button("spritesheet", &spritesheet);
    menu.add_button("proceed", &proceed);
    menu.add_button("back", &back);
}

void LevelEditNewScene::update(int delta, sf::RenderWindow &window)
{
    if (pl_state == in_menu) {
        return update_menu(delta, window);
    }
    return update_keyboard(delta, window);
}

void LevelEditNewScene::draw(sf::RenderWindow &window)
{
    if (pl_state == in_menu) {
        return draw_menu(window);
    }
    return draw_keyboard(window);
}

Scene::Status LevelEditNewScene::status()
{
    return state;
}

Scene *LevelEditNewScene::new_scene()
{
    return next_scene;
}

void LevelEditNewScene::reset_status()
{
    this->state = Scene::Status::nothing;
    this->next_scene = nullptr;
}

void LevelEditNewScene::update_menu(int delta, sf::RenderWindow &window)
{
    menu.update(delta, app_container.get_input(), window);
    auto pressed = this->menu.neg_edge_button();

    if (pressed == "proceed") {
        write_level_meta();
        this->next_scene = new LevelEditEditScene(this->size, this->name.get_label().toAnsiString());
        this->state = Scene::Status::push_scene;
    } else if (pressed == "name") {
        pl_state = in_keyboard;
        current_button = &name;
        keyboard.set_input("");
    } else if (pressed == "spritesheet") {
        pl_state = in_keyboard;
        current_button = &spritesheet;
        keyboard.set_input("");
    } else if (pressed == "back") {
        this->next_scene = nullptr;
        this->state = Scene::Status::pop_scene;
    }
}

void LevelEditNewScene::draw_menu(sf::RenderWindow &window)
{
    name_label.draw(window);
    spritesheet_label.draw(window);
    menu.draw(window);
}

void LevelEditNewScene::update_keyboard(int delta, sf::RenderWindow &window)
{
    keyboard.update(delta, window);
    if (app_container.get_input()->is_key_pressed(Input::escape) || keyboard.status() == Scene::Status::pop_scene) {
        keyboard.reset_status();
        app_container.get_logger()->info(keyboard.get_input().toAnsiString().c_str());
        current_button->set_label(keyboard.get_input());
        pl_state = in_menu;
    }
}

void LevelEditNewScene::draw_keyboard(sf::RenderWindow &window)
{
    keyboard.draw(window);
}

void LevelEditNewScene::write_level_meta()
{
    index.add(name.get_label().toAnsiString());
    index.save();

    std::string filename = name.get_label().toAnsiString();
    filename += ".txt";
    std::ofstream datafile(LEVELDIR + filename);
    datafile<<name.get_label().toUtf8().c_str()<<"\n";
    datafile<<"tex "<<spritesheet.get_label().toUtf8().c_str()<<"\n";
    datafile.close();
}
