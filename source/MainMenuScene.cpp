#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(sf::Vector2i size) : Scene(size)
{
    this->state = Scene::Status::nothing;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::update(int delta, sf::RenderWindow &window, Logger *logger)
{

}

void MainMenuScene::draw(sf::RenderWindow &window)
{

}

Scene::Status MainMenuScene::status()
{
    return this->state;
}

Scene *MainMenuScene::new_scene()
{
    return nullptr;
}
