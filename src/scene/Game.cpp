#include "Game.h"

#define CAMERA_LAG 10.0

namespace scene {
    Game::Game(sf::Vector2i size) :
        Scene(size),
        world()
    {
        this->main_window.reset(sf::FloatRect(0, 0, size.x, size.y));
    }

    Game::~Game()
    {
    }

    void Game::update(int delta, sf::RenderWindow &window)
    {
        if (first_loop) {
            first_loop = false;
            audio::MusicManager::play(audio::MusicManager::Song::playing_game);
        }
        world.update(delta, window);
        if (core::app_container.get_input()->is_key_pressed(core::Input::Key::escape)) {
            this->next_scene = nullptr;
            this->state = Scene::Status::pop_scene;
            audio::MusicManager::stop();
        }

        /* Camera Logic */
        auto target = this->world.get()->get_camera_target();
        if (target != nullptr) {
            auto camera_center = this->main_window.getCenter();
            auto target_camera_center = target->get_rect();
            target_camera_center.left = target_camera_center.left + (target_camera_center.width / 2);
            target_camera_center.top = target_camera_center.top + (target_camera_center.height / 2);

            sf::Vector2f camera_diff;
            camera_diff.x = (target_camera_center.left - camera_center.x) / CAMERA_LAG;
            camera_diff.y = (target_camera_center.top - camera_center.y) / CAMERA_LAG;

            this->main_window.move(camera_diff);
        }
        /* End Camera Logic */
    }

    void Game::draw(sf::RenderWindow &window)
    {
        window.setView(this->main_window);
        world.draw(window);
    }

    Scene::Status Game::status()
    {
        return this->state;
    }

    Scene *Game::new_scene()
    {
        return this->next_scene;
    }

    void Game::reset_status()
    {
        this->state = Scene::Status::nothing;
        this->next_scene = nullptr;
    }
};
