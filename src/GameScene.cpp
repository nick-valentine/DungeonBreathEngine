#include "GameScene.h"

GameScene::GameScene(sf::Vector2i size) :
    Scene(size),
    hero(sf::Vector2i(100, 100), sf::Vector2i(4, 4)),
    world(std::unique_ptr<TileSet>(new TileSet("overworld")), std::unique_ptr<WorldGenerator>(new WorldLoader(LEVELDIR "demo.txt"))),
    state(Scene::Status::nothing)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

GameScene::~GameScene()
{
}

void GameScene::update(int delta, sf::RenderWindow &window)
{
    if (first_loop) {
        first_loop = false;
        MusicManager::play(MusicManager::Song::playing_game);
    }
    this->hero.update(delta);
    world.update(delta, window);
    if (app_container.get_input()->is_key_pressed(Input::Key::escape)) {
        this->state = Scene::Status::pop_scene;
		MusicManager::stop();
    }
}

void GameScene::draw(sf::RenderWindow &window)
{
	app_container.get_logger()->info("drawing game");
    //window.setView(this->main_window);
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

void GameScene::reset_status()
{
	this->state = Scene::Status::nothing;
	this->next_scene = nullptr;
}