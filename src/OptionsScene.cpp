#include "OptionsScene.h"
#include "MainMenuScene.h"

OptionsScene::OptionsScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    next_scene(nullptr),
    lang_button_left(ui::left(sf::IntRect(10, 100, 50, 50))),
    lang_button_right(ui::right(sf::IntRect(110, 100, 50, 50))),
    back_button(sf::Rect<int>(10, size.y - 100, 300, 50), StringProvider::get("optionsmenu.back_button")),
    menu()
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    menu.add_button("lang_left", &lang_button_left);
    menu.add_button("lang_right", &lang_button_right);
    menu.add_button("back", &back_button);
}

void OptionsScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    this->menu.update(delta, input, window);
    
    std::string pressed = this->menu.pressed_button();
    if (pressed == "back") {
        this->next_scene = new MainMenuScene(this->size);
        this->state = Scene::Status::switch_scene;
    }
}

void OptionsScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->menu.draw(window);
}

Scene::Status OptionsScene::status()
{
    return this->state;
}

Scene *OptionsScene::new_scene()
{
    return this->next_scene;
}
