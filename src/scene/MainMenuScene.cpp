#include "MainMenuScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "TileSetScene.h"
#include "LevelEditScene.h"

MainMenuScene::MainMenuScene(sf::Vector2i size) : Scene(size)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    menu.add_button("level_editor", &level_edit_button);
    menu.add_button("tile_editor", &tile_editor_button);
    menu.add_button("play", &play_button);
    menu.add_button("options", &options_button);
    menu.add_button("exit", &exit_button);
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::update(int delta, sf::RenderWindow &window)
{
    if (first_loop) {
        first_loop = false;
        audio::MusicManager::play(audio::MusicManager::Song::main_menu);
    }

    this->menu.update(delta, app_container.get_input(), window);
    
    std::string pressed = this->menu.neg_edge_button();
    if (pressed == "play") {
        this->next_scene = new GameScene(this->size);
        this->state = Scene::Status::push_scene;
        audio::MusicManager::stop();
    }
    if (pressed == "options") {
        this->next_scene = new OptionsScene(this->size);
        this->state = Scene::Status::push_scene;
        audio::MusicManager::stop();
    }
    if (pressed == "tile_editor") {
        this->next_scene = new TileSetScene(this->size);
        this->state = Scene::Status::push_scene;
        audio::MusicManager::stop();
    }
    if (pressed == "level_editor") {
        this->next_scene = new LevelEditScene(this->size);
        this->state = Scene::Status::push_scene;
        audio::MusicManager::stop();
    }
    if (pressed == "exit") {
        this->next_scene = nullptr;
        this->state = Scene::Status::pop_scene;
        audio::MusicManager::stop();
    }
}

void MainMenuScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->menu.draw(window);
}

Scene::Status MainMenuScene::status()
{
    return this->state;
}

Scene *MainMenuScene::new_scene()
{
    return this->next_scene;
}

void MainMenuScene::reset_status()
{
    this->state = Scene::Status::nothing;
    this->next_scene = nullptr;
}
