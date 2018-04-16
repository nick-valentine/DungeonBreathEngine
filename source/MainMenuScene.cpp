#include "MainMenuScene.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene(sf::Vector2i size) :
    Scene(size),
    state(Scene::Status::nothing),
    play_button(sf::Rect<int>(10, size.y - 150, 135, 50), "New Game"),
    exit_button(sf::Rect<int>(10, size.y - 100, 70, 50), "Exit")
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

MainMenuScene::~MainMenuScene()
{
    MusicManager::stop();
}

void MainMenuScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::main_menu);
    }

    this->play_button.update(delta, window);
    this->exit_button.update(delta, window);

    if (this->play_button.pressed()) {
        this->next_scene = new GameScene(this->size);
        this->state = Scene::Status::switch_scene;
    }
    if (this->exit_button.pressed()) {
        this->next_scene = nullptr;
        this->state = Scene::Status::exit_program;
    }
}

void MainMenuScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->play_button.draw(window);
    this->exit_button.draw(window);
}

Scene::Status MainMenuScene::status()
{
    return this->state;
}

Scene *MainMenuScene::new_scene()
{
    return this->next_scene;
}
