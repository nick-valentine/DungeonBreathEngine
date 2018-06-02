#include "LevelEditActorSelectScene.h"

LevelEditActorSelectScene::LevelEditActorSelectScene(sf::Vector2i size) : Scene(size)
{
    std::vector<std::string> actor_index;

    for (const auto &i : index.get()) {
        actor_index.push_back(i);
    }

    actors.reserve(actor_index.size());
    for (size_t i = 0; i < actor_index.size(); ++i) {
        actors.push_back(
            TextButton(sf::IntRect(10, (i+1) * 50, 300, 50), Strings::utf8_to_sfml(actor_index[i]))
        );
        menu.add_button(actor_index[i], &actors[i]);
        std::cout<<actor_index[i]<<std::endl;
    }
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

void LevelEditActorSelectScene::update(int delta, sf::RenderWindow &window)
{
    menu.update(delta, app_container.get_input(), window);
    std::string pressed = this->menu.neg_edge_button();
    if (pressed != "") {
        this->selected = pressed;
        this->next_scene = nullptr;
        this->state = Scene::Status::pop_scene;
    }
}

void LevelEditActorSelectScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    menu.draw(window);
}

std::string LevelEditActorSelectScene::get_selected()
{
    return this->selected;
}

Scene::Status LevelEditActorSelectScene::status()
{
    return state;
}

Scene *LevelEditActorSelectScene::new_scene()
{
    return next_scene;
}

void LevelEditActorSelectScene::reset_status()
{
    state = Scene::Status::nothing;
    next_scene = nullptr;
}