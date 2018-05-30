#include "GameScene.h"

#define CAMERA_LAG 10.0

GameScene::GameScene(sf::Vector2i size) :
    Scene(size),
    world(std::unique_ptr<TileSet>(new TileSet("overworld")), std::unique_ptr<WorldGenerator>(new WorldLoader(LEVELDIR "demo.txt")))
{
    this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    this->actorman.spawn("enemy", sf::Vector2i(300, 300));
    auto h = this->actorman.spawn("hero", sf::Vector2i(100, 100));
    this->actorman.set_camera_target(h);
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
    this->actorman.update(delta);
    world.update(delta, window);
    if (app_container.get_input()->is_key_pressed(Input::Key::escape)) {
        this->next_scene = nullptr;
        this->state = Scene::Status::pop_scene;
        MusicManager::stop();
    }

    /* Camera Logic */
    auto target = this->actorman.get_camera_target();
    auto camera_center = this->main_window.getCenter();
    auto target_camera_center = target->get_rect();
    target_camera_center.left = target_camera_center.left + (target_camera_center.width / 2);
    target_camera_center.top = target_camera_center.top + (target_camera_center.height / 2);

    sf::Vector2f camera_diff;
    camera_diff.x = (target_camera_center.left - camera_center.x) / CAMERA_LAG;
    camera_diff.y = (target_camera_center.top - camera_center.y) / CAMERA_LAG;

    this->main_window.move(camera_diff);
    /* End Camera Logic */
}

void GameScene::draw(sf::RenderWindow &window)
{
    window.setView(this->main_window);
    world.draw(window);
    this->actorman.draw(window);
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
