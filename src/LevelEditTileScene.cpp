#include "LevelEditTileScene.h"

#define TILE_SIZE 64
#define CAMERA_LAG 10

LevelEditTileScene::LevelEditTileScene(sf::Vector2i size, std::string tileset) : Scene(size), tileset(tileset)
{
    cursor.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    cursor.setOutlineColor(sf::Color::Blue);
    cursor.setFillColor(sf::Color::White);
    cursor.setPosition(sf::Vector2f(0.0f, 0.0f));
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
}

void LevelEditTileScene::update(int delta, sf::RenderWindow &window)
{
    auto target_camera_center = cursor.getPosition();
    auto camera_center = this->main_window.getCenter();
    sf::Vector2f camera_diff;
    camera_diff.x = (target_camera_center.x - camera_center.x) / CAMERA_LAG;
    camera_diff.y = (target_camera_center.y - camera_center.y) / CAMERA_LAG;

    this->main_window.move(camera_diff);
}

void LevelEditTileScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    window.draw(cursor);
}

Scene::Status LevelEditTileScene::status()
{
    return this->state;
}

Scene *LevelEditTileScene::new_scene()
{
    return this->next_scene;
}

void LevelEditTileScene::reset_status()
{
    this->state = Scene::Status::nothing;
    this->next_scene = nullptr;
}
