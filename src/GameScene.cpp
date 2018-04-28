#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

GameScene::GameScene(sf::Vector2i size) :
    Scene(size),
    hero(sf::Vector2i(100, 100), sf::Vector2i(4, 4)),
    state(Scene::Status::nothing),
    tile_set(TextureMap::request("./GameData/img/Overworld.png"))
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    auto grass_tile = tile_set.make(sf::Vector2i(0,0));
    for (auto i = 0; i < 20; ++i) {
        for (auto j = 0; j < 20; ++j) {
            tileset.push_back(
                tile_set.spawn(
                    grass_tile, 
                    sf::Vector2i(
                        i * TileSet::tile_size(), 
                        j * TileSet::tile_size()
                    )
                )
            );
        }
    }
}

GameScene::~GameScene()
{
    MusicManager::stop();
}

void GameScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::playing_game);
    }
    this->hero.update(delta, input, logger);
    for (auto& value: tileset) {
        value.update(delta);
    }

    if (input->is_key_pressed(Input::Key::escape)) {
        this->state = Scene::Status::switch_scene;
        this->next_scene = new MainMenuScene(this->size);
    }
}

void GameScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    for (auto& value: tileset) {
        value.draw(window);
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
