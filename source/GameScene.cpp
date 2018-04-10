#include "GameScene.h"
#include "MainMenuScene.h"

GameScene::GameScene(sf::Vector2i size) :
    hero(sf::Vector2i(100, 100), sf::Vector2i(100, 100)),
    tile(sf::Rect<int>(0, 0, 200, 200), sf::Vector2i(0, 0)),
    Scene(size),
    state(Scene::Status::nothing)
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

GameScene::~GameScene()
{

}

void GameScene::update(int delta, sf::RenderWindow &window, Logger *logger)
{
        this->hero.update(delta, logger);
        this->tile.update(delta);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->state = Scene::Status::switch_scene;
            this->next_scene = new MainMenuScene(this->size);
        }
}

void GameScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    this->tile.draw(window);
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
