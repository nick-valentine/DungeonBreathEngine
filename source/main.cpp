#include <SFML/Graphics.hpp>

#include "ConfigLoader.h"
#include "Logger/ConsoleLogger.h"
#include "Hero.h"
#include "Scene.h"
#include "MainMenuScene.h"

void handleEvents(sf::RenderWindow &window);

int main()
{
    ConfigLoader::load();
    int resolution_x = ConfigLoader::get_int_option("resolution_x", 200);
    int resolution_y = ConfigLoader::get_int_option("resolution_y", 200);
    const int frame_frequency = 33333; // 1/30 of a second

    Logger *logger = new ConsoleLogger();

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "DungeonBreath");

    Scene *current_scene = new MainMenuScene(sf::Vector2i(resolution_x, resolution_y));

    sf::Clock timer;

    float delta = 0.0;
    while (window.isOpen()) {

        delta = timer.restart().asMicroseconds();
        sf::sleep(sf::microseconds(std::max(frame_frequency - delta, 0.0f)));

        handleEvents(window);
        current_scene->update(delta, window, logger);

        window.clear(sf::Color::Black);
        current_scene->draw(window);
        window.display();

        Scene::Status state = current_scene->status();
        if (state == Scene::Status::exit_program) {
            break;
        } else if (state == Scene::Status::switch_scene) {
            Scene *next = current_scene->new_scene();
            delete current_scene;
            current_scene = next;
        }
    }

    delete current_scene;
    delete logger;
    return 0;
}

void handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
