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
    int resolutionX = ConfigLoader::getIntOption("resolutionX", 200);
    int resolutionY = ConfigLoader::getIntOption("resolutionY", 200);
    const int frameFrequency = 33333; // 1/30 of a second

    Logger *logger = new ConsoleLogger();

    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "DungeonBreath");

    Scene *main_menu = new MainMenuScene(sf::Vector2i(resolutionX, resolutionY));
    Hero hero(sf::Vector2i(100,100), sf::Vector2i(100, 100));

    sf::Clock timer;

    float delta = 0.0;
    while (window.isOpen()) {

        delta = timer.restart().asMicroseconds();
        sf::sleep(sf::microseconds(std::max(frameFrequency - delta, 0.0f)));

        handleEvents(window);
        main_menu->update(delta, window, logger);
        hero.update(delta, logger);

        window.clear(sf::Color::Black);
        main_menu->draw(window);
        hero.draw(window);
        window.display();
    }

    delete main_menu;
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
