#include "LevelEditScene.h"
#include "LevelEditNewScene.h"
#include "LevelEditEditScene.h"

LevelEditScene::LevelEditScene(sf::Vector2i size) : Scene(size)
{
    std::vector<std::string> level_index;

    for (const auto &i : index.get()) {
        level_index.push_back(i);
    }

    levels.reserve(level_index.size());
    for (size_t i = 0; i < level_index.size(); ++i) {
        levels.push_back(
            TextButton(sf::IntRect(10, (i+1) * 50, 300, 50), Strings::utf8_to_sfml(level_index[i]))
        );
        menu.add_button(level_index[i], &levels[i]);
    }
    menu.add_button("new", &new_level);
    menu.add_button("exit_menu", &back);
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

void LevelEditScene::update(int delta, sf::RenderWindow &window)
{
    menu.update(delta, core::app_container.get_input(), window);
    std::string pressed = this->menu.neg_edge_button();

    if (pressed == "exit_menu") {
        this->next_scene = nullptr;
        this->state = Scene::Status::pop_scene;
    } else if (pressed == "new") {
        this->next_scene = new LevelEditNewScene(this->size);
        this->state = Scene::Status::push_scene;
    } else if (pressed != "") {
        this->next_scene = new LevelEditEditScene(this->size, pressed);
        this->state = Scene::Status::push_scene;
    }
}

void LevelEditScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    menu.draw(window);
}

Scene::Status LevelEditScene::status()
{
    return state;
}

Scene *LevelEditScene::new_scene()
{
    return next_scene;
}

void LevelEditScene::reset_status()
{
    state = Scene::Status::nothing;
    next_scene = nullptr;
}
