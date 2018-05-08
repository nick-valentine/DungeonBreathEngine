#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

GameScene::GameScene(sf::Vector2i size) :
    Scene(size),
    hero(sf::Vector2i(100, 100), sf::Vector2i(4, 4)),
    tile_set(TileSets::overworld()),
    state(Scene::Status::nothing)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));


    for (auto i = 0; i < 20; ++i) {
        for (auto j = 0; j < 20; ++j) {
            world.push_back(
                tile_set->spawn(
                    TileSets::Overworld::water_to_thick_br,
                    sf::Vector2i(
                        i * TileSet::tile_size()*2, 
                        j * TileSet::tile_size()*2
                    )
                )
            );
        }
    }
}

GameScene::~GameScene()
{
    MusicManager::stop();

    for (size_t i = 0; i < world.size(); ++i) {
        delete world[i];
    }
}

void GameScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::playing_game);
    }
    this->hero.update(delta, input, logger);
    for (auto& value: world) {
        value->update(delta);
    }

    if (input->is_key_pressed(Input::Key::escape)) {
        this->state = Scene::Status::switch_scene;
        this->next_scene = new MainMenuScene(this->size);
    }
}

void GameScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    for (auto& value: world) {
        value->draw(window);
    }
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
