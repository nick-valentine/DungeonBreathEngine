#include "GameScene.h"
#include "MainMenuScene.h"
#include <iostream>

GameScene::GameScene(sf::Vector2i size) :
    Scene(size),
    hero(sf::Vector2i(100, 100), sf::Vector2i(4, 4)),
    tile_set(TextureMap::request("./GameData/img/Overworld.png")),
    state(Scene::Status::nothing)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));

    auto grass_tile = tile_set.make_static(sf::Vector2i(0,0));
    auto water_one = tile_set.make_dynamic(
        std::vector<sf::Vector2i>{
            sf::Vector2i(0,1),
            sf::Vector2i(1,1),
            sf::Vector2i(2,1),
            sf::Vector2i(3,1),
        }
    );

    for (auto i = 0; i < 20; ++i) {
        for (auto j = 0; j < 20; ++j) {
            tileset.push_back(
                tile_set.spawn(
                    i * j % 2, 
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

    for (size_t i = 0; i < tileset.size(); ++i) {
        delete tileset[i];
    }
}

void GameScene::update(int delta, sf::RenderWindow &window, Input *input, Logger *logger)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::playing_game);
    }
    this->hero.update(delta, input, logger);
    for (auto& value: tileset) {
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
    for (auto& value: tileset) {
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
