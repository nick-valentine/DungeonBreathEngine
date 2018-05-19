#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

GameScene::GameScene(sf::Vector2i size, Input *input, Logger *logger) :
    Scene(size, input, logger),
    hero(sf::Vector2i(100, 100), sf::Vector2i(4, 4), input, logger),
    world(std::unique_ptr<TileSet>(new TileSet("overworld")), std::unique_ptr<WorldGenerator>(new WorldLoader(LEVELDIR "demo.txt"))),
    state(Scene::Status::nothing)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

GameScene::~GameScene()
{
    MusicManager::stop();
}

void GameScene::update(int delta, sf::RenderWindow &window)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::playing_game);
    }
    this->hero.update(delta, input, logger);
    world.update(delta, window, input, logger);
    if (input->is_key_pressed(Input::Key::escape)) {
        this->state = Scene::Status::switch_scene;
        this->next_scene = new MainMenuScene(this->size, this->input, this->logger);
    }
}

void GameScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    world.draw(window);
    this->hero.draw(window);
}

Scene::Status GameScene::status()
{
    return this->state;
}

Scene *GameScene::new_scene()
{
    return this->next_scene;
}
