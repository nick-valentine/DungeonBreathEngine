#include <SFML/Graphics.hpp>

#include "ConfigLoader.h"
#include "StringProvider.h"
#include "ConsoleLogger.h"
#include "Hero.h"
#include "Scene.h"
#include "Input.h"
#include "MainMenuScene.h"
#include "Script.h"

void handleEvents(sf::RenderWindow &window);

int main()
{
    ConfigLoader::load();
    sf::String lang = ConfigLoader::get_string_option("language", "eng");
    StringProvider::load(lang);

	Script s("main.lua");
	lua::config::add(s.s);
	s.call();

    int resolution_x = ConfigLoader::get_int_option("resolution_x", 200);
    int resolution_y = ConfigLoader::get_int_option("resolution_y", 200);
    const int frame_frequency = 33333; // 1/30 of a second

    ConsoleLogger logger;

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "DungeonBreath");

    Scene *current_scene = new MainMenuScene(sf::Vector2i(resolution_x, resolution_y));
    Input input;

    sf::Clock timer;

    int delta = 0;
    while (window.isOpen()) {

        delta = int(timer.restart().asMicroseconds());
        sf::sleep(sf::microseconds(sf::Int64(std::max(frame_frequency - float(delta), 0.0f))));

        handleEvents(window);
        current_scene->update(delta, window, &input, &logger);

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
